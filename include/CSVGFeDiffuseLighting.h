#ifndef CSVGFeDiffuseLighting_H
#define CSVGFeDiffuseLighting_H

#include <CSVGFeLighting.h>

class CSVGFeDiffuseLighting : public CSVGFeLighting {
 public:
  CSVG_OBJECT_DEF("feDiffuseLighting", CSVGObjTypeId::FE_DIFFUSE_LIGHTING)

  CSVGFeDiffuseLighting(CSVG &svg);
  CSVGFeDiffuseLighting(const CSVGFeDiffuseLighting &fe);

  CSVGFeDiffuseLighting *dup() const override;

  bool isDiffuse() const override { return true; }

  bool processOption(const std::string &name, const std::string &value) override;

  bool drawElement() override;

  void print(std::ostream &os, bool hier) const override;

  void printValues(std::ostream &os, bool flat=false) const override;

  friend std::ostream &operator<<(std::ostream &os, const CSVGFeDiffuseLighting &fe);
};

#endif
