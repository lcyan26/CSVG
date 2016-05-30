#ifndef CSVGLinearGradient_H
#define CSVGLinearGradient_H

#include <CSVGObject.h>
#include <CSVGTypes.h>
#include <CGenGradient.h>

class CSVGStop;
class CLinearGradient;

class CSVGLinearGradient : public CSVGObject {
 public:
  typedef std::vector<CSVGStop *> StopList;

 public:
  CSVG_OBJECT_DEF("linear_gradient", CSVGObjTypeId::LINEAR_GRADIENT)

  CSVGLinearGradient(CSVG &svg);
  CSVGLinearGradient(const CSVGLinearGradient &lg);

  CSVGLinearGradient *dup() const override;

  bool getBBox(CBBox2D &bbox) const {
    if (! x1_.isValid() || ! y1_.isValid() || ! x2_.isValid() || ! y2_.isValid())
      return false;

    double s = 1;

    bbox = CBBox2D(getX1().pxValue(s), getY1().pxValue(s),
                   getX2().pxValue(s), getY2().pxValue(s));

    return true;
  }

  CScreenUnits getX1(double x=0) const { return x1_.getValue(CScreenUnits(x)); }
  void setX1(const CScreenUnits &x1) { x1_ = x1; }

  CScreenUnits getY1(double y=0) const { return y1_.getValue(CScreenUnits(y)); }
  void setY1(const CScreenUnits &y1) { y1_ = y1; }

  CScreenUnits getX2(double x=1) const { return x2_.getValue(CScreenUnits(x)); }
  void setX2(const CScreenUnits &x2) { x2_ = x2; }

  CScreenUnits getY2(double y=0) const { return y2_.getValue(CScreenUnits(y)); }
  void setY2(const CScreenUnits &y2) { y2_ = y2; }

  void setBBox(const CBBox2D &bbox) {
    setX1(bbox.getXMin());
    setY1(bbox.getYMin());
    setX2(bbox.getXMax());
    setY2(bbox.getYMax());
  }

  bool getGTransformValid() const { return gtransform_.isValid(); }
  CMatrixStack2D getGTransform() const { return gtransform_.getValue(); }
  void setGTransform(const CMatrixStack2D &gtransform) { gtransform_ = gtransform; }

  bool getUnitsValid() const { return units_.isValid(); }
  CSVGCoordUnits getUnits() const { return units_.getValue(CSVGCoordUnits::OBJECT_BBOX); }
  void setUnits(CSVGCoordUnits units) { units_ = units; }

  bool getSpreadValid() const { return spread_.isValid(); }
  CGradientSpreadType getSpread() const { return spread_.getValue(CGRADIENT_SPREAD_PAD); }
  void setSpread(CGradientSpreadType spread) { spread_ = spread; }

  void addStop(CSVGStop *stop) { stops_.push_back(stop); }

  bool anyStops() const { return ! stops_.empty(); }

  const StopList &stops() const { return stops_; }

  bool processOption(const std::string &name, const std::string &value) override;

  void termParse();

  bool isDrawable() const override { return false; }

  void print(std::ostream &os, bool hier) const override;

  void setFillBuffer(CSVGBuffer *buffer, CSVGObject *obj);
  void setStrokeBuffer(CSVGBuffer *buffer, CSVGObject *obj);

  CLinearGradient *createGradient(CSVGObject *);

  void getEndPoints(CSVGObject *obj, double *x1, double *y1, double *x2, double *y2) const;

  friend std::ostream &operator<<(std::ostream &os, const CSVGLinearGradient &gradient);

 private:
  COptValT<CScreenUnits>        x1_;
  COptValT<CScreenUnits>        y1_;
  COptValT<CScreenUnits>        x2_;
  COptValT<CScreenUnits>        y2_;
  StopList                      stops_;
  COptValT<CMatrixStack2D>      gtransform_;
  COptValT<CSVGCoordUnits>      units_;
  COptValT<CGradientSpreadType> spread_;
};

#endif
