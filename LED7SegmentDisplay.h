#ifndef LED7SegmentDisplay
#define LED7SegmentDisplay

class LED7SegmentDisplay
{ 
public:
    LED7SegmentDisplay(unsigned int _numDigits, unsigned int* _cathodePins, unsigned int* _anodPins);
    void Init();

    void DisplayTime(unsigned int hours, unsigned int minutes);  
    void DisplayInt(int num);
	
private: 
  unsigned int numDigits = 4;
  unsigned int* cathodePins;
  unsigned int* anodPins;
  
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

  void DrawSegmentPicture(eSegmentPictures segmentPicture, bool needPickDot);
  
  private:
    void SetDigitNumberForChangePicture(unsigned char digitNumber);    
    void Clear();
    void DisplayDigit(unsigned char digitNumber, eSegmentPictures segmentPicture, bool needPickDot = false);
};

#endif	// LED7SegmentDisplay
