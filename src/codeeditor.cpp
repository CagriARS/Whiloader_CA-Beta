#include <QtWidgets>
#include "codeeditor.h"

/**
 * @brief Constructor for CodeEditor.
 * @param parent The parent widget.
 *
 * Initializes the CodeEditor and sets up the line number area, connections, and updates the line number area width.
 */
CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
}

/**
 * @brief Calculates the width required for the line number area.
 * @return The width of the line number area.
 */
int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());

    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 10 + fontMetrics().horizontalAdvance("  ") * digits;

    return space;
}

/**
 * @brief Updates the width of the line number area.
 * @param newBlockCount The new block count (not used).
 */
void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

/**
 * @brief Updates the line number area.
 * @param rect The rectangle that needs updating.
 * @param dy The vertical offset.
 */
void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

/**
 * @brief Handles the resize event.
 * @param e The resize event.
 *
 * Adjusts the geometry of the line number area when the editor is resized.
 */
void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

/**
 * @brief Highlights the current line.
 *
 * If highlighting is enabled, this function highlights the current line.
 */
void CodeEditor::highlightCurrentLine()
{
    if (isHighlightCurrentLineEnabled == true)
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);

        setExtraSelections(extraSelections);

        selection.cursor.clearSelection();
    }
}

/**
 * @brief Enables or disables current line highlighting.
 * @param status Boolean value to enable or disable highlighting.
 */
void CodeEditor::setHighlightEnabled(bool status)
{
    isHighlightCurrentLineEnabled = status;
}

/**
 * @brief Paint event for the line number area.
 * @param event The paint event.
 */
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int)blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignLeft, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}

/**
 * @brief Clears the text in the editor.
 */
void CodeEditor::clear()
{
    QPlainTextEdit::clear();
}

/**
 * @brief Appends text to the editor.
 * @param text The text to append.
 */
void CodeEditor::append(const QString &text)
{
    this->appendPlainText(text);
}

/**
 * @brief Handles the key press event.
 * @param event The key press event.
 *
 * This function overrides the default key press event to disable writing on the TextBrowser log.
 */
void CodeEditor::keyPressEvent(QKeyEvent *event){} /* Description of the overwritten function */

/**
 * @brief Handles the mouse press event.
 * @param event The mouse press event.
 *
 * This function overrides the default mouse press event to disable the mouse press in the TextBrowser log.
 */
void CodeEditor::mousePressEvent(QMouseEvent *event) {} /* Description of the overwritten function */
