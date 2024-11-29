#include <stdio.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "hi_pwm.h"
#include "hi_time.h"
#include "hi_gpio.h"
#include "unistd.h"

// 将频率数组改为 uint32_t
static const uint32_t g_tuneFreqs[] = {
    0L,       // 不使用
    955566L,  // 1046.5Hz  C6(do)
    851281L,  // 1174.7Hz  D6(re)
    758438L,  // 1318.5Hz  E6(mi)
    715871L,  // 1396.9Hz  F6(fa)
    637755L,  // 1568Hz    G6(so)
    568182L,  // 1760Hz    A6(la)
    506201L,  // 1975.5Hz  B6(si)
    1275510L  // 784Hz     G5(so)低八度
};

static const uint8_t g_scoreNotes[] = {
    1, 2, 3, 1,        1, 2, 3, 1,        3, 4, 5,  3, 4, 5,
    5, 6, 5, 4, 3, 1,  5, 6, 5, 4, 3, 1,  1, 8, 1,  1, 8, 1,
};

static const uint8_t g_scoreDurations[] = {
    4, 4, 4, 4,        4, 4, 4, 4,        4, 4, 8,  4, 4, 8,
    3, 1, 3, 1, 4, 4,  3, 1, 3, 1, 4, 4,  4, 4, 8,  4, 4, 8,
};

// 初始化PWM
int init_pwm(int pwmChannel) {
    // 在此实现PWM硬件初始化，假设PWM1通道已经正确初始化
    printf("PWM%d initialized.\n", pwmChannel);
    return 0;
}

// 设置PWM周期
int set_pwm_period(int pwmChannel, uint32_t freqDivisor) {
    // 设置PWM周期，freqDivisor应该是PWM的周期值
    printf("Set PWM period for channel %d: %u\n", pwmChannel, freqDivisor);
    return 0;
}

// 设置PWM占空比
int set_pwm_dutyCycle(int pwmChannel, uint32_t dutyCycle) {
    // 设置PWM占空比
    printf("Set PWM duty cycle for channel %d: %u\n", pwmChannel, dutyCycle);
    return 0;
}

// 启用PWM
int set_pwm_enable(int pwmChannel, int isEnable) {
    if (isEnable == 1) {
        printf("Enable PWM channel %d\n", pwmChannel);
    } else {
        printf("Disable PWM channel %d\n", pwmChannel);
    }
    return 0;
}

int main(int argc, char **argv) {
    int pwmChannel = 1;  // 使用通道1，假设你知道正确的通道号
    int isEnable = 1; // 启用PWM
    init_pwm(pwmChannel);

    printf("BeeperMusicTask start!\n");

    // 演奏音乐
    for (size_t i = 0; i < sizeof(g_scoreNotes)/sizeof(g_scoreNotes[0]); i++) {
        uint32_t tune = g_scoreNotes[i];
        uint32_t freqDivisor = g_tuneFreqs[tune];
        uint32_t tuneInterval = g_scoreDurations[i] * (125 * 1000); // 微秒

        // 设置PWM周期和占空比
        set_pwm_period(pwmChannel, freqDivisor);
        set_pwm_dutyCycle(pwmChannel, freqDivisor / 2);
        set_pwm_enable(pwmChannel, isEnable);

        // 等待音符的时间
        usleep(tuneInterval);

        // 停止PWM信号
        set_pwm_enable(pwmChannel, 0);

        // 两个音符间稍微延时
        usleep(20 * 1000); // 20ms
    }

    return 0;
}
