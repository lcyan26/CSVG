#ifndef CQSVGSymbol_H
#define CQSVGSymbol_H

#include <CQSVGObject.h>
#include <CSVGSymbol.h>

class CQSVG;

class CQSVGSymbol : public CQSVGObject, public CSVGSymbol {
  Q_OBJECT

 public:
  CQSVGSymbol(CQSVG *svg);
};

#endif
