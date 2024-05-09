#include <ncurses.h>
#include <string>
#include <array>
#include <cmath>
#include <tuple>
#include "digitalclock.hpp"

DigitalClock::DigitalClock (int x, int y) : x(x), y(y) { }

AsciiArt DigitalClock::colon {
    R"( _ )", 
    R"((_))", 
    R"( _ )", 
    R"((_))"
};
AsciiArt DigitalClock::zero {
    R"(  __  )", 
    R"( /  \ )", 
    R"((  0 ))", 
    R"( \__/ )"
};
AsciiArt DigitalClock::one {
    R"(  __  )", 
    R"( /  \ )", 
    R"((_/ / )", 
    R"( (__) )"
};
AsciiArt DigitalClock::two {
    R"( ____ )", 
    R"((___ \)", 
    R"( / __/)", 
    R"((____))"
};
AsciiArt DigitalClock::three {
    R"( ____ )", 
    R"(( __ \)", 
    R"( (__ ()", 
    R"((____/)"
};
AsciiArt DigitalClock::four {
    R"(  ___ )", 
    R"( / _ \)", 
    R"((__  ()", 
    R"(  (__/)"
};
AsciiArt DigitalClock::five {
    R"(  ___ )", 
    R"( / __))", 
    R"((___ \)", 
    R"((____/)"
};
AsciiArt DigitalClock::six {
    R"(  ___ )", 
    R"( / __))", 
    R"((  _ \)", 
    R"( \___/)"
};
AsciiArt DigitalClock::seven {
    R"( ____ )", 
    R"((__  ))", 
    R"(  / / )", 
    R"( (_/  )"
};
AsciiArt DigitalClock::eight {
    R"( ____ )", 
    R"(/ _  \)", 
    R"() _  ()", 
    R"(\____/)"
};
AsciiArt DigitalClock::nine {
    R"( ___  )", 
    R"(/ _ \ )", 
    R"(\__  ))", 
    R"((___/ )"
};

/**
 * Draw given ascii art to screen
 * @param dim will render in dark-gray instead of white
*/
void DigitalClock::DrawAsciiArt(AsciiArt rows, int x, int y, bool dim = false) {
    if (dim) attron(A_DIM);
    for (int i = 0; i < 4; i++) {
        mvprintw(y + i, x, rows[i].c_str());
    }
    attroff(A_DIM);
}

/**
 * Get AsciiArt object for given single-digit number
 * Font: Graceful-6x4 by Mikhael Goikhman, http://migo.n3.net/, 20/Jan/2002.
*/
AsciiArt DigitalClock::GetAsciiArt(int digit) {
    digit = digit % 10; // only accept 0-9
    switch (digit) {
        case 0:
            return zero;
        case 1:
            return one;
        case 2:
            return two;
        case 3:
            return three;
        case 4:
            return four;
        case 5:
            return five;
        case 6:
            return six;
        case 7:
            return seven;
        case 8:
            return eight;
        case 9:
            return nine;
        default:   
            return zero;
    }
}

/**
 * Get AsciiArt object for given character
 * Font: Graceful-6x4 by Mikhael Goikhman, http://migo.n3.net/, 20/Jan/2002.
*/
AsciiArt DigitalClock::GetAsciiArt(char character) {
    switch (character) {
        case ':':
            return colon;
        default:
            return zero;
    }
}

/**
 * Render a digital clock to the screen
 * @param timerElapsedMs milliseconds elapsed since timer start
 * @param timerIsStopped timer isn't actively incrementing
*/
void DigitalClock::Draw(int timerElapsedMs, bool timerIsStopped = false) const {
    AsciiArt zeroArt = GetAsciiArt(0);
    AsciiArt colonArt = GetAsciiArt(':');

    int elapsedMs = timerElapsedMs;
    int elapsedSec = elapsedMs / 1000;
    int elapsedMin = elapsedSec / 60;
    int elapsedHr = elapsedMin / 60;

    int secModMin = elapsedSec % 60;
    int minModHr = elapsedMin % 60;

    int currentPosX = x;
    int posY = y;

    auto willDigitOverflow = [elapsedMs, timerIsStopped] (int overflowMs) -> bool {
        return !timerIsStopped && ((elapsedMs % overflowMs) > (overflowMs - DIM_DURATION));
    };

    // hours
    DrawAsciiArt(GetAsciiArt(elapsedHr), currentPosX, posY, willDigitOverflow(36000000));
    // colon
    DrawAsciiArt(colonArt, currentPosX += DIGIT_WIDTH, posY);
    
    // minutes (tens)
    if (minModHr < 10) {
        DrawAsciiArt(zeroArt, currentPosX += COL_WIDTH, posY, willDigitOverflow(600000));
    } else {
        DrawAsciiArt(GetAsciiArt((int) std::floor(minModHr / 10)), currentPosX += COL_WIDTH, posY, willDigitOverflow(600000));
    }

    // minutes (ones)
    DrawAsciiArt(GetAsciiArt(minModHr % 10), currentPosX += DIGIT_WIDTH, posY, willDigitOverflow(60000));
    // colon
    DrawAsciiArt(colonArt, currentPosX += DIGIT_WIDTH, posY); // colon

    // seconds (tens)
    if (secModMin < 10) {
        DrawAsciiArt(zeroArt, currentPosX += COL_WIDTH, posY, willDigitOverflow(10000));
    } else {
        DrawAsciiArt(GetAsciiArt((int) std::floor(secModMin / 10)), currentPosX += COL_WIDTH, posY, willDigitOverflow(10000));
    }

    // seconds (ones)
    DrawAsciiArt(GetAsciiArt(secModMin % 10), currentPosX += DIGIT_WIDTH, posY, willDigitOverflow(1000));
}

void DigitalClock::SetXY(std::tuple<int, int> pos) {
    x = std::get<0>(pos);
    y = std::get<1>(pos);
}