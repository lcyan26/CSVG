#ifndef CSVGFeFlood_H
#define CSVGFeFlood_H

#include <CSVGFilterBase.h>

class CSVGBuffer;

class CSVGFeFlood : public CSVGFilterBase {
 public:
  CSVG_OBJECT_DEF("feFlood", CSVGObjTypeId::FE_FLOOD)

  CSVGFeFlood(CSVG &svg);
  CSVGFeFlood(const CSVGFeFlood &fe);

  CSVGFeFlood *dup() const override;

  std::string getFilterIn() const { return filterIn_.getValue("FilterGraphic"); }
  void setFilterIn(const std::string &s) { filterIn_ = s; }

  std::string getFilterOut() const { return filterOut_.getValue("FilterGraphic"); }
  void setFilterOut(const std::string &s) { filterOut_ = s; }

  double getOpacity() const { return opacity_.getValue(1); }
  void setOpacity(double r) { opacity_ = r; }

  bool processOption(const std::string &name, const std::string &value) override;

  void draw() override;

  void filterImage(CSVGBuffer *outBuffer);

  void print(std::ostream &os, bool hier) const override;

  friend std::ostream &operator<<(std::ostream &os, const CSVGFeFlood &fe);

 private:
  COptValT<std::string> filterIn_;
  COptValT<std::string> filterOut_;
  COptValT<CRGBA>       color_;
  COptValT<double>      opacity_;
};

#endif
