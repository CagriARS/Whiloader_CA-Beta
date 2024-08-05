#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

QT_END_NAMESPACE

class LineNumberArea;

/**
 * @class CodeEditor
 * @brief A custom text editor widget with line number area and syntax highlighting.
 *
 * The CodeEditor class extends QPlainTextEdit to provide additional functionalities
 * such as a line number area and optional syntax highlighting.
 */
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for CodeEditor.
     * @param parent The parent widget.
     */
    CodeEditor(QWidget *parent = nullptr);

    /**
     * @brief Paint event for the line number area.
     * @param event The paint event.
     */
    void lineNumberAreaPaintEvent(QPaintEvent *event);

    /**
     * @brief Calculate the width of the line number area.
     * @return The width of the line number area.
     */
    int lineNumberAreaWidth();

    /**
     * @brief Enable or disable line highlighting.
     * @param status Boolean value to enable or disable highlighting.
     */
    void setHighlightEnabled(bool status);

    /**
     * @brief Clear the text editor.
     */
    void clear();

    /**
     * @brief Append text to the editor.
     * @param text The text to append.
     */
    void append(const QString &text);

protected:
    /**
     * @brief Handle the resize event.
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief Handle the mouse press event. Disables mouse press in the TextBrowser log.
     * @param event The mouse press event.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handle the key press event. Disables writing in the TextBrowser log.
     * @param event The key press event.
     */
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    /**
     * @brief Update the width of the line number area when the block count changes.
     * @param newBlockCount The new block count.
     */
    void updateLineNumberAreaWidth(int newBlockCount);

    /**
     * @brief Highlight the current line.
     */
    void highlightCurrentLine();

    /**
     * @brief Update the line number area.
     * @param rect The rectangle to update.
     * @param dy The vertical offset.
     */
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;  /**< The widget for the line number area. */
    bool isHighlightCurrentLineEnabled = false;  /**< Flag to enable or disable current line highlighting. */
};

/**
 * @class LineNumberArea
 * @brief A widget for displaying line numbers.
 *
 * The LineNumberArea class is a helper class for CodeEditor to display line numbers.
 */
class LineNumberArea : public QWidget
{
public:
    /**
     * @brief Constructor for LineNumberArea.
     * @param editor The associated CodeEditor.
     */
    LineNumberArea(CodeEditor *editor) : QWidget(editor)
    {
        codeEditor = editor;
    }

    /**
     * @brief Size hint for the line number area.
     * @return The recommended size for the line number area.
     */
    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    /**
     * @brief Paint event for the line number area.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;  /**< The associated CodeEditor. */
};

#endif // CODEEDITOR_H
