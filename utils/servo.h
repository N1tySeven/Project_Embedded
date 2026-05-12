#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>

// Servo parameters for 8MHz F_CPU and Prescaler 8
// TOP = 20000 for 50Hz (20ms)
// Continuous Rotation Servo:
//   1500 = Stop
#define SERVO_STOP_PW  1500  // 1.5ms - Stop

// ปรับความเร็วในการหมุน (offset จากจุด stop)
// ยิ่งค่าน้อยลง (เข้าใกล้ 0) จะหมุนช้าลง, ค่าสูงสุดคือ 500 (หมุนเต็มสปีด)
#define SERVO_SPEED_OFFSET 500

#define SERVO_CW       (SERVO_STOP_PW - SERVO_SPEED_OFFSET)  // หมุนเปิด (ทวน/ตามเข็ม ขึ้นอยู่กับติดตั้ง)
#define SERVO_CCW      (SERVO_STOP_PW + SERVO_SPEED_OFFSET)  // หมุนปิด

// ระยะเวลาที่ใช้ในการหมุน (มิลลิวินาที) - ปรับค่านี้เพื่อให้เปิด/ปิดประตูได้พอดี
#define SERVO_ROTATION_TIME_MS  400

void servo_init(void);
void servo_stop(void);
void servo_lock(void);
void servo_unlock(void);

#endif
