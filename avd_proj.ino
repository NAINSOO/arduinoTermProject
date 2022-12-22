/***
 * 어드밴쳐 디자인 프로젝트 10조 : 두더지 게임 프로젝트
 * 사용 디바이스 : 16x2 LCD, 7-segment, 가속도 센서, LED 4개, pull-down 버튼 4개, 초음파 센서
 * 
 * 60초 동안 진행되는 스코어 게임.
 */
#define DISTMODE 4
#define ACCELMODE 5
#define JODOMODE 6


int gameClockBase = 0;
int leds[4] = {2,3,4,5};
int buttons[4] = {8,9,10,11};

/**
 * 남은 시간을 7-segment를 표현하는 것은 기술적으로 어려울 것 같다. 왜냐하면 게임에서 버튼을 입력받거나 하는 시간을이 1초를 넘어서 일정한 시점에 시간을 갱신해주는 것은 
 * 멀티 쓰레드가 필요하다.
 */

/**
 * 7segment를 통해서 점수를 출력
 */
void printScore(int score){
  
}

/**
 * 센서 입력 함수 모음
 * int getJODO(void);
 * int getAccel(void);
 * int getDistance(void);
 */
/**
 * 조도 센서 입력 받기
 */
 int getJODO(void){
  return 100;
 }

 /**
  * 가속도 센서 입력 받기
  *   --> 가속도 센서 알아본 후 x,y,z 축중 게임에 적용하기 가장 용이한 축을 선택해야함
  *   ---> x축이 선택되었다면 x축만 return 하기.
  * 
  */

  int getAccel(void){
    return 100;
  }

 /**
  * 초음파 센서 거리 입력 받기 
  * 
  * 
  */
int getDistance(void){
  return 100; // 컴파일 오류 안나게 하려고 넣었음
}



/**
 *  LCD에 게임 명령어 출력하기
 *  매개변수인 mode와 command에 따라서 유저에게 적절한 명령어를 전달
 */

void printCommand(int mode, int command){
  if(mode == DISTMODE){
     if(command == 0){
        //인식되는 거리를 가깝게 해라
     }
     else{
      //인식되는 거리를 멀게 해라
     }
  }
  else if(mode == ACCELMODE){
    if(command == 0){
       //왼쪽으로 기울기
    }
    else{
      // 오른쪽으로 기울기
    }
  }
  else if(mode =JODOMODE){
    if (command == 0){
      //불빛을 줄여라
    }
    else{
      //불빛을 높여라
    }
  }
  else{
   //두더지 모드 입니다. 
  }
}


void setup() {
  gameClockBase  =  millis();

  for(int i=0;i<4;i++){
    pinMode(leds[i],OUTPUT);
    pinMode(buttons[i],INPUT);
  }
  
  Serial.begin(9600);
}

int getGameClock(){
  return (millis() - gameClockBase);
}

int getInputInterval(int base){
  return (millis() - base);
}

int inputState(int select){
  boolean isHit = false;
  int base = millis() ;
  
  while(getInputInterval(base)<2000){
    if(digitalRead(select)){
        isHit = true;
        Serial.println("button push");
        break;
      }
   }

   if(isHit ==true)return 1;
   else return 0;
}

int distState(int select){
  boolean isHit = false;
  int base = millis() ;
  while(getInputInterval(base)<3000){
    if (select){
      if(getDistance() >50){
        isHit=true;
        break;
      }
    }
    else{
      if(getDistance()<50){
        isHit=true;
        break;
    }
   }
   if(isHit ==true)return 1;
   else return 0;
}
}
int jodoState(int select){
  boolean isHit = false;
  int base = millis() ;
  while(getInputInterval(base)<3000){
    if (select){
      if(getJODO() >300){
        isHit=true;
        break;
      }
    }
    else{
      if(getJODO()<300){
        isHit=true;
        break;
    }
   }
   if(isHit ==true)return 1;
   else return 0;
}
}
int accelState(int select){
  boolean isHit = false;
  int base = millis() ;
  while(getInputInterval(base)<3000){
    if (select){
      if(getAccel() >0){
        isHit=true;
        break;
      }
    }
    else{
      if(getAccel()<0){
        isHit=true;
        break;
    }
   }
   if(isHit ==true)return 1;
   else return 0;
  }
}


int getScore(int value,int mode){
  if(value){
    if(mode==DISTMODE){
      return 20;
    }
    else if(mode == ACCELMODE){
      return 20;
    }
    else if(mode == JODOMODE){
      return 15;
    }else{
      return 10;
    }
    
  }
}

void loop() {
  Serial.println("game start");

  int score = 0;
  while(abs(getGameClock()) < 30000){
    Serial.println(getGameClock());
    int num = random(7);//0 부터 3까지 두더지 모드 4부터 6까지 센서 인식 모드
    
    if (num == JODOMODE){
      int isHit = 0;
      Serial.println("jodo mode");
      int command = random(2);
      printCommand(JODOMODE, command);
      isHit = jodoState(command);
      score += getScore(isHit,JODOMODE);
    }
    else if(num == DISTMODE){
      int isHit = 0;
      Serial.println("dist mode");
      int command = random(2);
      printCommand(DISTMODE, command);
      isHit = distState(command);
      score += getScore(isHit,DISTMODE);
    }
    else if(num==ACCELMODE){
      Serial.println("accel mode");
      int command = random(2);
      int isHit = 0;
      printCommand(ACCELMODE, command);
      isHit = accelState(command);
      score += getScore(isHit,ACCELMODE);
      
    }else{
      Serial.println(String("button mode : ")+num);
      int selectedLed = leds[num];
      int selectedBtn = buttons[num];
      int isHit = 0;
    
      digitalWrite(selectedLed, 1);
      isHit = inputState(selectedBtn);
      digitalWrite(selectedLed, 0);

      score += getScore(isHit,0);
    }

    
    delay(2500);
    }
  gameClockBase  =  millis();
  Serial.println(String("game over and score is : ")+ score); 
  printScore(score);
  
}
