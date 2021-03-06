#ifndef CQSVGFeBlend_H
#define CQSVGFeBlend_H

#include <CQSVGObject.h>
#include <CSVGFeBlend.h>

class CQSVG;

class CQSVGFeBlend : public CQSVGObject, public CSVGFeBlend {
  Q_OBJECT

 public:
  CQSVGFeBlend(CQSVG *svg);
};

#endif
