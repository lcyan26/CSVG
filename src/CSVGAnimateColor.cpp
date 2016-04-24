#include <CSVGAnimateColor.h>
#include <CSVG.h>
#include <CSVGLog.h>
#include <CSVGUtil.h>

/* Attributes:
    <Core>
    <Conditional>
    animation event attributes
    xlink attributes
    animation attribute target attributes
    animation timing attributes
    animation value attributes
    animation addition attributes
    presentation attributes
    <External>
*/

CSVGAnimateColor::
CSVGAnimateColor(CSVG &svg) :
 CSVGAnimateBase(svg)
{
}

CSVGAnimateColor::
CSVGAnimateColor(const CSVGAnimateColor &animateColor) :
 CSVGAnimateBase(animateColor),
 type_    (animateColor.type_),
 additive_(animateColor.additive_)
{
}

CSVGAnimateColor *
CSVGAnimateColor::
dup() const
{
  return new CSVGAnimateColor(*this);
}

bool
CSVGAnimateColor::
processOption(const std::string &opt_name, const std::string &opt_value)
{
  if (CSVGAnimateBase::processOption(opt_name, opt_value))
    return true;

  std::string str;

  if      (svg_.stringOption(opt_name, opt_value, "type"    , str))
    type_ = str;
  else if (svg_.stringOption(opt_name, opt_value, "additive", str))
    additive_ = str;
  else
    return false;

  return true;
}

void
CSVGAnimateColor::
animate(double t)
{
  if      (getAttributeName() == "fill") {
    CRGBA fromColor, toColor;

    svg_.decodeColorString(getFrom(), fromColor);
    svg_.decodeColorString(getTo  (), toColor  );

    CRGBA c = fromColor*(1 - t) + toColor*t;

    getParent()->setFillColor(c);

    svg_.redraw();
  }
  else if (getAttributeName() == "stroke") {
    CRGBA fromColor, toColor;

    svg_.decodeColorString(getFrom(), fromColor);
    svg_.decodeColorString(getTo  (), toColor  );

    CRGBA c = fromColor*(1 - t) + toColor*t;

    getParent()->setStrokeColor(c);

    svg_.redraw();
  }
}

void
CSVGAnimateColor::
print(std::ostream &os, bool hier) const
{
  if (hier) {
    os << "<animateColor";

    CSVGAnimateBase::printValues(os);

    printNameValue(os, "type"    , type_    );
    printNameValue(os, "additive", additive_);

    os << "/>" << std::endl;
  }
  else
    os << "animateColor ";
}

std::ostream &
operator<<(std::ostream &os, const CSVGAnimateColor &animateColor)
{
  animateColor.print(os, false);

  return os;
}
