#ifndef CSVGFeOffset_H
#define CSVGFeOffset_H

#include <CSVGFilterBase.h>

class CSVGBuffer;

class CSVGFeOffset : public CSVGFilterBase {
 public:
  CSVG_OBJECT_DEF("feOffset", CSVGObjTypeId::FE_OFFSET)

  CSVGFeOffset(CSVG &svg);
  CSVGFeOffset(const CSVGFeOffset &offset);

  CSVGFeOffset *dup() const override;

  bool hasFilterIn() const { return filterIn_.isValid(); }
  std::string getFilterIn() const { return filterIn_.getValue("FilterGraphic"); }
  void setFilterIn(const std::string &s) { filterIn_ = s; }

  bool hasFilterOut() const { return filterOut_.isValid(); }
  std::string getFilterOut() const { return filterOut_.getValue("FilterGraphic"); }
  void setFilterOut(const std::string &s) { filterOut_ = s; }

  double getDX() const { return dx_.getValue(0); }
  void setDX(double d) { dx_ = d; }

  double getDY() const { return dy_.getValue(0); }
  void setDY(double d) { dy_ = d; }

  bool processOption(const std::string &name, const std::string &value) override;

  void draw() override;

  void print(std::ostream &os, bool hier) const override;

  friend std::ostream &operator<<(std::ostream &os, const CSVGFeOffset &filter);

 private:
  COptValT<std::string> filterIn_;
  COptValT<std::string> filterOut_;
  COptValT<double>      dx_;
  COptValT<double>      dy_;
};

#endif
