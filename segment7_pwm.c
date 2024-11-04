#include <softPwm.h>
#include <stdio.h>
#include <wiringPi.h>

const int gpio[8] = {1, 4, 5, 6, 26, 27, 28, 29};  // 設定GPIO的腳位
const int num[][8] = {
    // 設定七段顯示器的數字
    // a b c d e f g DP (分別代表七段顯示器的位置)
    {1, 1, 1, 1, 1, 1, 0, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1, 0},  // 2
    {1, 1, 1, 1, 0, 0, 1, 0},  // 3
    {0, 1, 1, 0, 0, 1, 1, 0},  // 4
    {1, 0, 1, 1, 0, 1, 1, 0},  // 5
    {1, 0, 1, 1, 1, 1, 1, 0},  // 6
    {1, 1, 1, 0, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1, 0},  // 8
    {1, 1, 1, 1, 0, 1, 1, 0},  // 9
    {1, 1, 1, 0, 1, 1, 1, 0},  // A
    {0, 0, 1, 1, 1, 1, 1, 0},  // b
    {1, 0, 0, 1, 1, 1, 0, 0},  // C
    {0, 1, 1, 1, 1, 0, 1, 0},  // d
    {1, 0, 0, 1, 1, 1, 1, 0},  // E
    {1, 0, 0, 0, 1, 1, 1, 0}   // F
    // 加入其他英文字母
};

void pwm_display_digit(int number_to_display) {
    int val;
    for (val = 0; val <= 50; val++) {  // 從暗變亮
        // 同步調整所有LED的亮度
        for (int i = 0; i < 8; i++) {
            if (num[number_to_display][i] == 1) {
                softPwmWrite(gpio[i], val);
            } else {
                softPwmWrite(gpio[i], 0);  // 確保非顯示的段是關閉的
            }
        }
        delay(10);
    }
    for (val = 50; val >= 0; val--) {  // 從亮變暗
        // 同步調整所有LED的亮度
        for (int i = 0; i < 8; i++) {
            if (num[number_to_display][i] == 1) {
                softPwmWrite(gpio[i], val);
            } else {
                softPwmWrite(gpio[i], 0);  // 確保非顯示的段是關閉的
            }
        }
        delay(10);
    }
}

void display_str_start() {
  // 此 function 應呼叫 pwm_display_digit
}

void display_str_open() {
  // 此 function 應呼叫 pwm_display_digit
}

void display_str_close() {
  // 此 function 應呼叫 pwm_display_digit
}

int main(void) {
    if (wiringPiSetup() == -1)  // 設定WiringPi
        return 0;

    int i = 0;
    while (i < 8) {
        softPwmCreate(gpio[i], 0, 100);  // 設定軟體PWM值介於 0 ~ 100 之間
        // pinMode(gpio[i], OUTPUT);
        i++;
    }  // while()

    // 驗收時註解以下段落
    while (1) {
        int number = 0;
        while (number <= 15) {
            pwm_display_digit(number);
            number++;
        }  // while()
    }  // while()
    // 驗收時註解以上段落

    display_str_start();
    delay(100);
    display_str_open();
    delay(100);
    display_str_close();
    delay(100);
    return 0;
}  // main()