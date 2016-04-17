#include <CQSVGCanvas.h>
#include <CQSVG.h>
#include <CQSVGWindow.h>
#include <CQSVGObject.h>
#include <CQSVGRenderer.h>
#include <CQPropertyTree.h>
#include <QMouseEvent>

CQSVGCanvas::
CQSVGCanvas(CQSVGWindow *window, CQSVG *svg) :
 QWidget(window), window_(window), svg_(svg)
{
  setObjectName("canvas");

  renderer_ = new CQSVGRenderer;

  svg_->setRenderer(renderer_);

  opainter_ = new QPainter;

  setFocusPolicy(Qt::StrongFocus);

  setMouseTracking(true);
}

void
CQSVGCanvas::
redraw()
{
  renderer_->setSize(width(), height());

  double bw = svg_->getBlock()->getWidth ()*scale_;
  double bh = svg_->getBlock()->getHeight()*scale_;

  renderer_->setPixelRange(bw, bh);

  renderer_->setBackground(svg_->CSVG::background());

  if (width() != oimage_.width() || height() != oimage_.height())
    oimage_ = QImage(QSize(width(), height()), QImage::Format_ARGB32);

  oimage_.fill(0);

  opainter_->begin(&oimage_);

  CMatrix2D matrix;

  matrix.setScale(scale_, scale_);

  svg_->draw(matrix, scale_);

  opainter_->end();
}

void
CQSVGCanvas::
resizeEvent(QResizeEvent *)
{
  redraw();
}

void
CQSVGCanvas::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.fillRect(rect(), svg_->background());

  renderer_->paint(&painter);

  //painter_->setWorldMatrixEnabled(false);

  painter.drawImage(0, 0, oimage_);

  //painter_->setWorldMatrixEnabled(true);
}

void
CQSVGCanvas::
mousePressEvent(QMouseEvent *e)
{
  CQPropertyTree *tree = window_->tree();

  if (tree) {
    tree->blockSignals(true);

    tree->clearSelection();
  }

  window_->deselectAllObjects();

  CPoint2D w;

  renderer_->pixelToWindow(CPoint2D(e->pos().x(), e->pos().y()), w);

  std::vector<CSVGObject *> objects;

  svg_->getObjectsAtPoint(w, objects);

  //std::cout << objects.size() << std::endl;

  for (const auto &obj : objects) {
    CQSVGObject *qobj = dynamic_cast<CQSVGObject *>(obj);
    if (! qobj) continue;

    qobj->setSelected(true);

    if (tree)
      tree->selectObject(qobj);

    //std::string id = obj->getObjName() + std::to_string(obj->getInd());
    //std::cout << id << std::endl;
  }

  if (tree)
   tree->blockSignals(false);

  redraw();

  update();
}

void
CQSVGCanvas::
mouseMoveEvent(QMouseEvent *e)
{
  CPoint2D w;

  renderer_->pixelToWindow(CPoint2D(e->pos().x(), e->pos().y()), w);

  std::vector<CSVGObject *> objects;

  svg_->getBlock()->getAllChildren(objects);

  for (const auto &obj : objects) {
    CQSVGObject *qobj = dynamic_cast<CQSVGObject *>(obj);
    if (! qobj) continue;

    if (obj->inside(w)) {
      if (! obj->getInside()) {
        obj->setInside(true);

        obj->handleEvent(CSVGEventType::MOUSE_OVER);
      }
    }
    else {
      if (obj->getInside()) {
        obj->setInside(false);

        obj->handleEvent(CSVGEventType::MOUSE_OUT);
      }
    }
  }

  window_->showPos(e->pos(), QPointF(w.x, w.y));
}

void
CQSVGCanvas::
mouseReleaseEvent(QMouseEvent *e)
{
  CPoint2D w;

  renderer_->pixelToWindow(CPoint2D(e->pos().x(), e->pos().y()), w);

  std::vector<CSVGObject *> objects;

  svg_->getObjectsAtPoint(w, objects);

  for (const auto &obj : objects) {
    CQSVGObject *qobj = dynamic_cast<CQSVGObject *>(obj);
    if (! qobj) continue;

    qobj->object()->handleEvent(CSVGEventType::CLICK);
  }
}

void
CQSVGCanvas::
keyPressEvent(QKeyEvent *ke)
{
  if      (ke->key() == Qt::Key_Plus)
    scale_ *= 1.20;
  else if (ke->key() == Qt::Key_Minus)
    scale_ /= 1.20;
  else if (ke->key() == Qt::Key_Home)
    scale_ = 1;

  redraw();

  update();
}

void
CQSVGCanvas::
drawSelected()
{
  oimage_.fill(0);

  opainter_->begin(&oimage_);

  std::vector<CSVGObject *> objects;

  CSVGBlock *block = svg_->getBlock();

  CQSVGObject *qblock = dynamic_cast<CQSVGObject *>(svg_->getBlock());

  if (qblock)
    qblock->drawSelected();

  block->getAllChildren(objects);

  for (const auto &obj : objects) {
    CQSVGObject *qobj = dynamic_cast<CQSVGObject *>(obj);
    if (! qobj) continue;

    qobj->drawSelected();
  }

  opainter_->end();

  update();
}

void
CQSVGCanvas::
drawRect(const CBBox2D &bbox, const QColor &c)
{
  CPoint2D p1, p2;

  renderer_->windowToPixel(bbox.getLL(), p1);
  renderer_->windowToPixel(bbox.getUR(), p2);

  opainter_->setPen(c);

  opainter_->drawLine(p1.x, p1.y, p2.x, p1.y);
  opainter_->drawLine(p2.x, p1.y, p2.x, p2.y);
  opainter_->drawLine(p2.x, p2.y, p1.x, p2.y);
  opainter_->drawLine(p1.x, p2.y, p1.x, p1.y);
}