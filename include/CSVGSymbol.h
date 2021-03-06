#ifndef CSVGSymbol_H
#define CSVGSymbol_H

#include <CSVGObject.h>

class CSVGSymbol : public CSVGObject {
 public:
  CSVG_OBJECT_DEF("symbol", CSVGObjTypeId::SYMBOL)

  CSVGSymbol(CSVG &svg);
  CSVGSymbol(const CSVGSymbol &symbol);

  CSVGSymbol *dup() const override;

  CSVGPreserveAspect preserveAspect() const {
    return preserveAspect_.getValue(CSVGPreserveAspect()); }
  void setPreserveAspect(const CSVGPreserveAspect &a) { preserveAspect_ = a; }

  bool processOption(const std::string &name, const std::string &value) override;

  void moveBy(const CVector2D &delta) override;
  void resizeTo(const CSize2D &size) override;
  void rotateBy(double da, const CPoint2D &c) override;

  bool canFlatten() const override { return false; }

  bool isDrawable() const override { return false; }

  void print(std::ostream &os, bool hier) const override;

  void printValues(std::ostream &os, bool flat=false) const override;

  friend std::ostream &operator<<(std::ostream &os, const CSVGSymbol &group);

 private:
  COptValT<CSVGPreserveAspect> preserveAspect_;
};

#endif
