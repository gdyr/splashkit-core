//
//  text_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 16/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "text_input.h"

#include "input_driver.h"
#include "text.h"
#include "utility_functions.h"

#include <vector>
#include <map>
using namespace std;

void draw_collected_text(color clr, font fnt, int font_size, float x, float y, drawing_options opts)
{
    window current = current_window();
    if ( not current ) return;
    
    string ct = current->input_text;
    draw_text(ct, clr, fnt, font_size, x, y, opts);
    font_style style = get_font_style(fnt);
    
    set_font_style(fnt, static_cast<font_style>(static_cast<int>(style) | static_cast<int>(UNDERLINE_FONT)));
    draw_text(current->composition, clr, fnt, font_size, x + text_length(ct, fnt, font_size), y, opts);
    
    set_font_style(fnt, style);
}

bool reading_text()
{
    return reading_text(current_window());
}

bool reading_text(window wind)
{
    return VALID_PTR(wind, WINDOW_PTR) and wind->reading_text;
}

void start_reading_text(rectangle rect)
{
    start_reading_text(current_window(), rect);
}

void start_reading_text(window wind, rectangle rect)
{
    if ( INVALID_PTR(wind, WINDOW_PTR))
    {
        raise_warning("Attempting to start reading text with invalid window");
        return;
    }
    
    sk_start_reading_text(wind, rect.x, rect.y, rect.width, rect.height);
}

string text_input()
{
    return text_input(current_window());
}

string text_input(window wind)
{
    if ( INVALID_PTR(wind, WINDOW_PTR) )
    {
        raise_warning("Attempting to read input text from invalid window");
        return "";
    }
    
    return wind->input_text + wind->composition;
}