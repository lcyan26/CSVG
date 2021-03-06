#include <CSVGFePointLight.h>
#include <CSVG.h>

CSVGFePointLight::
CSVGFePointLight(CSVG &svg) :
 CSVGFilterBase(svg)
{
}

CSVGFePointLight::
CSVGFePointLight(const CSVGFePointLight &fe) :
 CSVGFilterBase(fe)
{
}

CSVGFePointLight *
CSVGFePointLight::
dup() const
{
  return new CSVGFePointLight(*this);
}

bool
CSVGFePointLight::
processOption(const std::string &opt_name, const std::string &opt_value)
{
  double r;

  if      (svg_.realOption(opt_name, opt_value, "x", &r))
    x_ = r;
  else if (svg_.realOption(opt_name, opt_value, "y", &r))
    y_ = r;
  else if (svg_.realOption(opt_name, opt_value, "z", &r))
    z_ = r;
  else
    return CSVGFilterBase::processOption(opt_name, opt_value);

  return true;
}

bool
CSVGFePointLight::
drawElement()
{
  return false;
}

void
CSVGFePointLight::
print(std::ostream &os, bool hier) const
{
  if (hier) {
    os << "<fePointLight";

    printValues(os);

    os << "/>" << std::endl;
  }
  else
    os << "fePointLight ";
}

void
CSVGFePointLight::
printValues(std::ostream &os, bool flat) const
{
  CSVGObject::printValues(os, flat);

  CSVGFilterBase::printValues(os, flat);

  printNameValue(os, "x", x_);
  printNameValue(os, "y", y_);
  printNameValue(os, "z", z_);
}

std::ostream &
operator<<(std::ostream &os, const CSVGFePointLight &fe)
{
  fe.print(os, false);

  return os;
}
