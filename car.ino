

#include <IRremote.h>

////////// IR REMOTE CODES //////////
#define F 16736925 // FORWARD
#define B 16754775 // BACK
#define L 16720605 // LEFT
#define R 16761405 // RIGHT
#define S 16712445 // STOP
#define KEY_0 16730805
#define KEY_1 16738455
#define KEY_2 16750695
#define KEY_3 16756815
#define KEY_4 16724175
#define KEY_5 16718055
#define KEY_6 16743045
#define KEY_7 16716015
#define KEY_8 16726215
#define KEY_9 16734885
#define KEY_ *16728765
#define KEY_ # 16732845
#define UNKNOWN_F 5316027    // FORWARD
#define UNKNOWN_B 2747854299 // BACK
#define UNKNOWN_L 1386468383 // LEFT
#define UNKNOWN_R 553536955  // RIGHT
#define UNKNOWN_S 3622325019 // STOP

#define RECV_PIN 12

/*define channel enable output pins*/
#define ENA 5 // Left  wheel speed
#define ENB 6 // Right wheel speed
/*define logic control output pins*/
#define IN1 7        // Left  wheel forward
#define IN2 8        // Left  wheel reverse
#define IN3 9        // Right wheel reverse
#define IN4 11       // Right wheel forward
#define carSpeed 150 // initial speed of car >=0 to <=255
#define carSpeeda 70
#define carSpeedb 225
#define carSpeedc 180

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;
unsigned long preMillis;

/**
 * BEGIN DEFINE FUNCTIONS
 */

void forward()
{
    analogWrite(ENA, carSpeedc);
    analogWrite(ENB, carSpeedc);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("go forward!");
}
void back()
{
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("go back!");
}
void left()
{
    analogWrite(ENA, carSpeedc);
    analogWrite(ENB, carSpeedc);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("go left!");
}
void right()
{
    analogWrite(ENA, carSpeedc);
    analogWrite(ENB, carSpeedc);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("go right!");
}
void sol()
{
    analogWrite(ENA, carSpeedb);
    analogWrite(ENB, carSpeedb);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("turn left 90 degree!");
    delay(700);
}
void sag()
{
    analogWrite(ENA, carSpeedc);
    analogWrite(ENB, carSpeedc);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("turn right 90 degree!");
    delay(500);
}
void circle()
{
    analogWrite(ENA, carSpeedb);
    analogWrite(ENB, carSpeeda);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("round");
    delay(700);
}
void stop()
{
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    Serial.println("STOP!");
}

void setup()
{
    Serial.begin(9600);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    stop();
    irrecv.enableIRIn();
}

void loop()
{
    if (irrecv.decode(&results))
    {
        preMillis = millis();
        val = results.value;
        Serial.println(val);
        irrecv.resume();
        switch (val)
        {
        case F:
        case UNKNOWN_F:
            forward();
            break;
        case B:
        case UNKNOWN_B:
            back();
            break;
        case L:
        case UNKNOWN_L:
            left();
            break;
        case R:
        case UNKNOWN_R:
            right();
            break;
        case S:
        case UNKNOWN_S:
            stop();
            break;
        case KEY_1:
            sol();
            stop();
            break;
        case KEY_2:
            sag();
            stop();
            break;
        case KEY_3:
            circle();
            ;
            break;
        case KEY_4:
        {
            forward();
            delay(700);
            sag();
            delay(300);
            forward();
            delay(700);
            sag();
            delay(300);
            forward();
            delay(700);
            sag();
            delay(300);
            forward();
            delay(700);
            stop();
            break;
        }

        default:
            break;
        }
    }
    else
    {
        if (millis() - preMillis > 500)
        {
            stop();
            preMillis = millis();
        }
    }
}
