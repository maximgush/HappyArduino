// display 1234
// select pin for cathode
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int dp = 8;

// select pin for anode
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;

class LED7SegmentDisplay
{  
  struct SegmentPictureLEDValues
  {
    bool LEDValues[7] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW };
  };
  enum eSegmentPictures { sp0, sp1, sp2, sp3, sp4, sp5, sp6, sp7, sp8, sp9, spMinus, stEmpty, spCount };
  bool SegmentPictureLEDValues[spCount][7] = {
      { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW },  // 0
      { LOW, HIGH, HIGH, LOW, LOW, LOW, LOW },      // 1
      { HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH },   // 2
      { HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH },   // 3
      { LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH },    // 4
      { HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH },   // 5
      { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH },  // 6
      { HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW },     // 7
      { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH }, // 8
      { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH },  // 9  
      { LOW, LOW, LOW, LOW, LOW, LOW, HIGH },       // - 
      { LOW, LOW, LOW, LOW, LOW, LOW, LOW }         // Ничего
  };

  unsigned int numDigits = 4;
  unsigned int* cathodePins;
  unsigned int* anodPins;

  void DrawSegmentPicture(eSegmentPictures segmentPicture, bool needPickDot)
  {
    if (segmentPicture == stEmpty)
      return;
      
    for (int i = 0; i < 7; ++i)
      digitalWrite(cathodePins[i], SegmentPictureLEDValues[segmentPicture][i]);

    digitalWrite(cathodePins[7], needPickDot);
  }
  
  public:
    LED7SegmentDisplay(unsigned int _numDigits, unsigned int* _cathodePins, unsigned int* _anodPins)
    : numDigits(_numDigits), cathodePins(_cathodePins), anodPins(_anodPins)
    {
      
    }

    void Init()
    {
        for (int i = 0; i < 8; ++i)
           pinMode(cathodePins[i], OUTPUT);

        for (int i = 0; i < numDigits; ++i)
           pinMode(anodPins[i], OUTPUT);
    }
  
    void Display4(int num)
    { 
      int minValue = -pow(10,numDigits-1) + 1;     
      int maxValue = pow(10,numDigits) - 1;
      if (num < minValue || num > maxValue)
      {
        for (int i = 0; i < numDigits; ++i)
          DisplayDigit(i, spMinus);
        return;
      }

      bool isNegative = num < 0;
      if (isNegative)
        num = -num;

      // Разбиваем число на цифры
      int i = 0;
      for (; i < numDigits; i++ )
      {
        eSegmentPictures picture = num % 10;
        num = num / 10;

        // Tckb
        if (num != 0 || picture != sp0 || i == 0)
          DisplayDigit(i, picture);               
      
        if (num == 0)
          break;
      }

      if (isNegative)
        DisplayDigit(i+1, spMinus);
    }
  private:
    void SetDigitNumberForChangePicture(unsigned char digitNumber)
    {
        // Мы должны сделать LOW напряжение на пине соответствующем числу ячейке
        // которую будем выставлять
        for (int i = 0; i < numDigits; i++)
          digitalWrite(anodPins[i], digitNumber != i ? HIGH : LOW);
    }
    
    void Clear()  // clear the screen
    {
      // TODO сделать таблицу
      for (int i = 0; i < 8; ++i)
        digitalWrite(cathodePins[i], LOW);
    }
    
    void DisplayDigit(unsigned char digitNumber, eSegmentPictures segmentPicture, bool needPickDot = false)//  take x as coordinate and display number
    {
      SetDigitNumberForChangePicture(digitNumber);      
      DrawSegmentPicture(segmentPicture, needPickDot);      
      Clear();
    }
};

unsigned int displayCathodePins[8] = {1,2,3,4,5,6,7,8};
unsigned int displayAnodePins[4] = {9,10,11,12};
LED7SegmentDisplay display(4, displayCathodePins, displayAnodePins );

void setup()
{
   display.Init();
}
/////////////////////////////////////////////////////////////
void loop()
{
  delay(1000/100);
  int time = millis() / 1000;
  display.Display4(-798); 
}
///////////////////////////////////////////////////////////////
