//
// Created by Thodemar on 15-6-2023.
//

#include "ht1632c.hpp"
#include "hwlib.hpp"



void ht1632c::write_pin(hwlib::pin_out & pin , bool state){
    pin.write(state);
    pin.flush();
}

void ht1632c::write_membit(bool state){
    write_pin(WR,0);
    write_pin(DATA, state);
    write_pin(WR,1);
}


void ht1632c::cs_set_multi(int chip, bool state){
    if (chip == 1) {
        write_pin(CS1, state);
    } else if (chip == 2) {
        write_pin(CS2, state);
    } else if (chip == 3) {
        write_pin(CS3, state);
    } else {
        write_pin(CS4, state);
    }

}
ht1632c::ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1)
    :
    DATA(DATAi), WR(WRi),
    CS1(CS1), CS2(hwlib::pin_out_dummy), CS3(hwlib::pin_out_dummy), CS4(hwlib::pin_out_dummy),
    matrix{},
    amountMatrixen(1)
{
    write_pin(CS1,1);

    write_pin(WR,1);
    write_pin(DATA,0);

    // For some reason this needs to be here otherwise it doesn't work when you run it the first time
    hwlib::wait_ms(1);
    write_pin(CS1,0);
    write_pin(CS1,1);
}


ht1632c::ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1, hwlib::pin_out & CS2)
        :
        DATA(DATAi), WR(WRi),
        CS1(CS1), CS2(CS2), CS3(hwlib::pin_out_dummy), CS4(hwlib::pin_out_dummy),
        matrix{},
        amountMatrixen(2)
{
    write_pin(CS1,1);
    write_pin(CS2,1);

    write_pin(WR,1);
    write_pin(DATA,0);

    // For some reason this needs to be here otherwise it doesn't work when you run it the first time
    hwlib::wait_ms(1);
    write_pin(CS1,0);
    write_pin(CS1,1);
    write_pin(CS2,0);
    write_pin(CS2,1);


}

ht1632c::ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1, hwlib::pin_out & CS2,
                 hwlib::pin_out & CS3)
        :
        DATA(DATAi), WR(WRi),
        CS1(CS1), CS2(CS2), CS3(CS3), CS4(hwlib::pin_out_dummy),
        matrix{},
        amountMatrixen(3)
{
    write_pin(CS1,1);
    write_pin(CS2,1);
    write_pin(CS3,1);

    write_pin(WR,1);
    write_pin(DATA,0);

    // For some reason this needs to be here otherwise it doesn't work when you run it the first time
    hwlib::wait_ms(1);
    write_pin(CS1,0);
    write_pin(CS1,1);
    write_pin(CS2,0);
    write_pin(CS2,1);
    write_pin(CS3,0);
    write_pin(CS3,1);

}

ht1632c::ht1632c(hwlib::pin_out & DATAi, hwlib::pin_out & WRi, hwlib::pin_out & CS1, hwlib::pin_out & CS2,
                 hwlib::pin_out & CS3, hwlib::pin_out & CS4)
        :
        DATA(DATAi), WR(WRi),
        CS1(CS1), CS2(CS2), CS3(CS3), CS4(CS4),
        matrix{},
        amountMatrixen(4)
{
    write_pin(CS1,1);
    write_pin(CS2,1);
    write_pin(CS3,1);
    write_pin(CS4,1);

    write_pin(WR,1);
    write_pin(DATA,0);

    // For some reason this needs to be here otherwise it doesn't work when you run it the first time
    hwlib::wait_ms(1);
    write_pin(CS1,0);
    write_pin(CS1,1);
    write_pin(CS2,0);
    write_pin(CS2,1);
    write_pin(CS3,0);
    write_pin(CS3,1);
    write_pin(CS4,0);
    write_pin(CS4,1);
}


void ht1632c::flush() {
    for( int chip = 1; chip <= amountMatrixen; chip++){
            if (chip == 1){
                write_pin(CS1,0);
            } else if (chip == 2){
                write_pin(CS2,0);
            } else if (chip == 3){
                write_pin(CS3,0);
            } else {
                write_pin(CS4,0);
            }

            write_membit(1);
            write_membit(0);
            write_membit(1);

            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);

            for (int i = 0; i < 32; i++) {
                for (int j = 8*(chip-1); j < 8*chip; j++) {
                    write_membit(matrix[j][i]);
                }
            }

            if (chip == 1){
                write_pin(CS1,1);
            } else if (chip == 2){
                write_pin(CS2,2);
            } else if (chip == 3){
                write_pin(CS3,3);
            } else {
                write_pin(CS4,4);
            }

        }

}

void ht1632c::set_xy(int x, int y, bool state) {
    matrix[y][x] = state;
}

// Empty's the matrix with a for loop in a for loop
void ht1632c::empty_matrix() {
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 32; j++){
            matrix[i][j] = 0;

        }
    }
}

void ht1632c::fill_matrix() {
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 32; j++){
            matrix[i][j] = 1;

        }
    }
}

void ht1632c::empty_screen() {
    for( int chip = 1; chip <= amountMatrixen; chip++){
            if (chip == 1){
                write_pin(CS1,0);
            } else if (chip == 2){
                write_pin(CS2,0);
            } else if (chip == 3){
                write_pin(CS3,0);
            } else {
                write_pin(CS4,0);
            }

            write_membit(1);
            write_membit(0);
            write_membit(1);

            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);
            write_membit(0);

            for (int i = 0; i < 32; i++) {
                for (int j = 8*(chip-1); j < 8*chip; j++) {
                    write_membit(0);
                }
            }

            if (chip == 1){
                write_pin(CS1,1);
            } else if (chip == 2){
                write_pin(CS2,1);
            } else if (chip == 3){
                write_pin(CS3,1);
            } else {
                write_pin(CS4,1);
            }

        }

}



int ht1632c::get_amountMatrixen() {
    return amountMatrixen;
}

void ht1632c::send_command(bool command[12] ,int chip){
    cs_set_multi(chip,0);

    for (int i = 0;i < 12;i++)
    {
        write_membit(command[i]);
    }

    cs_set_multi(chip,1);
}


void ht1632c::begin() {
    bool SYS_EN[12] = {1,0,0,0,0,0,0,0,0,0,1,0};
    bool LED_ON[12] = {1,0,0,0,0,0,0,0,0,1,1,0};
    bool BLINK_OFF[12] = {1,0,0,0,0,0,0,1,0,0,0,0};
    bool vier[12] = {1,0,0,0,0,0,1,0,1,0,0,0};
    bool RC_MASTER_MODE[12] = {1,0,0,0,0,0,1,1,0,0,0,0};
    bool COM_OPTION_NMOS_8COM[12] = {1,0,0,0,0,1,0,0,0,0,0,0};
    bool PWM_16[12] = {1,0,0,1,0,1,0,1,1,1,1,0};


    for (int chip = 1; chip <= amountMatrixen; chip++) {
        send_command(SYS_EN,chip);
        send_command(LED_ON,chip);
        send_command(BLINK_OFF,chip);
        send_command(vier,chip);
        send_command(RC_MASTER_MODE,chip);
        send_command(COM_OPTION_NMOS_8COM,chip);
        send_command(PWM_16,chip);

    }
}