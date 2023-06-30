//
// Created by Thodemar on 15-6-2023.
//

#include "hwlib.hpp"
//#include <vector>


#ifndef IPASS_HT1632C_HPP
#define IPASS_HT1632C_HPP


/// @file

/// \brief
/// ht1632c class
/// \details
/// This is a class that allows you to write information to a ht1632c.
/// The information for each light is stored in a 32x32 array.
/// Because the size of the array it has a max capacity for 4 chips to be send to.
///
/// XY cordinates start at 0,0
///
/// The class allows for the changing of individual lights or multiple at the same time

class ht1632c {
private:
    hwlib::pin_out &DATA;
    hwlib::pin_out &WR;
    hwlib::pin_out &CS1;
    hwlib::pin_out &CS2;
    hwlib::pin_out &CS3;
    hwlib::pin_out &CS4;
    bool matrix[32][32];
    int amountMatrixen;

    // Combines the .write() and .flush() function from hwlib for a pin
    void write_pin(hwlib::pin_out & pin , bool state);

    // Writes one bit on the DATA line and pulls the WR line low and high
    void write_membit(bool state);

    // Sends a command to the matrix. The command it needs to send is given in the form of an 12 lenght boolean array.
    void send_command(bool command[12],int chip);


    // Sets a different chip select based on in the chip input. Input is 1, 2, 3 or 4 and state says if it needs to by high or low.
    void cs_set_multi(int chip, bool state);


public:
    /// \brief
    /// Constructor for 1 chip
    /// \details
    /// Constructor initializes the DATA, WR and CS pins and throws them high.
    /// Also sets the amountMatrixen on 1 and fills the matrix with zero's.
    ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1);

    /// \brief
    /// Constructor for 2 chips
    /// \details
    /// Constructor initializes the DATA, WR and CS pins and throws them high.
    /// Also sets the amountMatrixen on 2 and fills the matrix with zero's.
    ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1, hwlib::pin_out & CS2);

    /// \brief
    /// Constructor for 3 chips
    /// \details
    /// Constructor initializes the DATA, WR and CS pins and throws them high.
    /// Also sets the amountMatrixen on 3 and fills the matrix with zero's.
    ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1, hwlib::pin_out & CS2,
            hwlib::pin_out & CS3);

    /// \brief
    /// Constructor for 4 chips
    /// \details
    /// Constructor initializes the DATA, WR and CS pins and throws them high.
    /// Also sets the amountMatrixen on 4 and fills the matrix with zero's.
    ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1, hwlib::pin_out & CS2,
            hwlib::pin_out & CS3, hwlib::pin_out & CS4);

    /// \brief
    /// flushes the matrix onto the screens
    /// \details
    /// completely reflushes the screens with new information from the matrix array.
    void flush();

    /// \brief
    /// Sets everything in array matrix to 0
    /// \details
    /// sets every value in the array matrix to 0.
    void empty_matrix();


    /// \brief
    /// Sets everything in array matrix to 1
    /// \details
    /// sets every value in the array matrix to 1.
    void fill_matrix();

    /// \brief
    /// Empties the screen
    /// \details
    /// Clears the screen of any lit up lights. DO NOTE: This does not clear the matrix so with the next flush the old values will be projected.
    void empty_screen();

    /// \brief
    /// Sets a specific XY coördinate
    /// \details
    /// Sets the status based on input state in of an specific XY coordinate in the matrix array. DO NOTE: lowest XY is 0,0.
    void set_xy(int x, int y, bool state);


    /// \brief
    /// Getter for amountMatrixen
    /// \details
    /// Gives the value that is stored in de variable amountMatrixen
    int get_amountMatrixen();

    /// \brief
    /// Sets the matrixboard(s) up
    /// \details
    /// Sets up the matrixboard(s) voor use as a LED 8 X 32 matrix. DO NOTE: this needs to run for the matrix to show anything
    void begin();

};


#endif //IPASS_HT1632C_HPP
