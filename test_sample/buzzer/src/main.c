/*
 * Copyright (c) 2022 Unionman Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "hilog/log.h"
#include "um_pwm.h"


static const uint16_t g_tuneFreqs[] = {
    0L,     // 不使用
    955,566L, // 1046.5Hz  C6(do)
    851,281L, // 1174.7Hz  D6(re)
    758,438L, // 1318.5Hz  E6(mi)
    715,871L, // 1396.9Hz  F6(fa)
    637,755L, // 1568Hz    G6(so)
    568,182L, // 1760Hz    A6(la)
    506,201L, // 1975.5Hz  B6(si)
    1,275,510L  // 784Hz     G5(so)低八度
};

// 曲谱音符数组：《两只老虎》。
// 简谱：http://www.jianpu.cn/pu/33/33945.htm
static const uint8_t g_scoreNotes[] = {
    1, 2, 3, 1,        1, 2, 3, 1,        3, 4, 5,  3, 4, 5,
    5, 6, 5, 4, 3, 1,  5, 6, 5, 4, 3, 1,  1, 8, 1,  1, 8, 1, // 最后两个 5 应该是低八度的，链接图片中的曲谱不对，声音到最后听起来不太对劲
};

// 曲谱音符数组：《蜜雪冰城主题曲》
// static const uint8_t g_scoreNotes[] = {
//     3, 5, 5, 6, 5, 3, 1, 1, 2, 3, 3, 2, 1, 2,
//     3, 5, 5, 6, 5, 3, 1, 1, 2, 3, 3, 2, 2, 1,
//     4, 4, 4, 6, 5, 5, 3, 2,
//     3, 5, 5, 6, 5, 3, 1, 1, 2, 3, 3, 2, 2, 1
// };

// 曲谱时值数组：《两只老虎》。
// 根据简谱记谱方法转写。
// 4/4拍中下面划一条线是半拍，划两条线是四分之一拍，点是顺延半拍
static const uint8_t g_scoreDurations[] = {
    4, 4, 4, 4,        4, 4, 4, 4,        4, 4, 8,  4, 4, 8,
    3, 1, 3, 1, 4, 4,  3, 1, 3, 1, 4, 4,  4, 4, 8,  4, 4, 8,
};

// 曲谱时值数组：《蜜雪冰城主题曲》
// static const uint8_t g_scoreDurations[] = {
//     2, 2, 3, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 8,
//     2, 2, 3, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 8,
//     4, 4, 2, 6, 4, 3, 1, 8,
//     2, 2, 3, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 8
// };

// 主线程函数
int main(int argc, char **argv)
{
    int pwmChannel = PWM1;
    int isEnable = PWM_IS_ENABLED;
    init_pmw(pwmChannel);

    (void)arg;

    printf("BeeperMusicTask start!\r\n");   // 日志输出


    // 演奏音乐
    // 使用循环遍历曲谱音符数组
    for (size_t i = 0; i < sizeof(g_scoreNotes)/sizeof(g_scoreNotes[0]); i++) {
        // 获取音符，也就是分频倍数数组元素的下标
        uint32_t tune = g_scoreNotes[i];
        // 获取分频倍数
        uint16_t freqDivisor = g_tuneFreqs[tune];
        // 获取音符时间
        // 适当拉长时间，四分之一拍用时125ms，每小节2s
        uint32_t tuneInterval = g_scoreDurations[i] * (125*1000);
        // 日志输出
        // 开始输出PWM信号，占空比50%
        set_pwm_period(pwmChannel, freqDivisor);
        set_pwm_dutyCycle(pwmChannel,freqDivisor/2);
        set_pwm_enable(pwmChannel, isEnable);
        // 等待音符时间，参数的单位是微秒（千分之一毫秒）
        usleep(tuneInterval);
        // 停止输出PWM信号
        set_pwm_enable(pwmChannel, PWM_NOT_ENABLED);
        // 停止一个音符后，等待20ms，让两次发音有个间隔，听起来更自然一些
        usleep(20*1000);
    }

    return 0;
}
