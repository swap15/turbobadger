// ================================================================================
// == This file is a part of TinkerBell UI Toolkit. (C) 2011-2012, Emil Seger�s  ==
// ==                   See tinkerbell.h for more information.                   ==
// ================================================================================

#ifndef TB_TOGGLE_CONTAINER_H
#define TB_TOGGLE_CONTAINER_H

#include "tb_widgets_common.h"

namespace tinkerbell {

/** TBToggleContainer is a widget that toggles a property when its value
	change between 0 and 1. TOGGLE specifies what property will toggle.
	This is useful f.ex to toggle a whole group of child widgets depending
	on the value of some other widget. By connecting the TBToggleContainer
	with a widget connection, this can happen completly automatically. */
class TBToggleContainer : public TBWidget
{
public:
	// For safe typecasting
	WIDGET_SUBCLASS("TBToggleContainer", TBWidget);

	TBToggleContainer();

	/** Defines what should toggle when the value changes. */
	enum TOGGLE {
		TOGGLE_NOTHING,		///< Nothing happens (the default)
		TOGGLE_ENABLED,		///< Enabled/disabled state
		TOGGLE_OPACITY,		///< Opacity 1/0
		TOGGLE_EXPANDED		///< Expanded/collapsed (In parent axis direction)
	};

	/** Set what should toggle when the value changes. */
	void SetToggle(TOGGLE toggle);
	TOGGLE GetToggle() const { return m_toggle; }

	/** Set if the toggle state should be inverted. */
	void SetInvert(bool invert);
	bool GetInvert() const { return m_invert; }

	/** Get the current value, after checking the invert mode. */
	bool GetIsOn() const { return m_invert ? !m_value : !!m_value; }

	/** Set the value of this widget. 1 will turn on the toggle, 0 will turn it off (or
		the opposite if the invert mode is set). */
	virtual void SetValue(int value);
	virtual int GetValue() { return m_value; }

	virtual PreferredSize GetPreferredSize();
private:
	void UpdateInternal();
	TOGGLE m_toggle;
	bool m_invert;
	int m_value;
};

/** TBSectionHeader is just a thin wrapper for a TBButton that is in toggle
	mode with the skin TBSectionHeader by default. It is used as the clickable
	header in TBSection that toggles the section. */
class TBSectionHeader : public TBButton
{
public:
	// For safe typecasting
	WIDGET_SUBCLASS("TBSectionHeader", TBButton);

	TBSectionHeader();

	virtual bool OnEvent(const TBWidgetEvent &ev);
};

/** TBSection is a widget with a header that when clicked toggles its children
	on and off (using a internal TBToggleContainer with TOGGLE_EXPANDED).

	The header is a TBSectionHeader.

	The skin names of the internal widgets are:
		TBSection				- This widget itself.
		TBSection.layout		- The layout that wraps the header and the container.
		TBSection.container		- The toggle container with the children that expands/collapses.
*/

class TBSection : public TBWidget
{
public:
	// For safe typecasting
	WIDGET_SUBCLASS("TBSection", TBWidget);

	TBSection();
	~TBSection();

	TBLayout *GetLayout() { return &m_layout; }
	TBSectionHeader *GetHeader() { return &m_header; }
	TBToggleContainer *GetContainer() { return &m_toggle_container; }

	/** Set the text of the text field. */
	virtual bool SetText(const char *text) { return m_header.SetText(text); }
	virtual bool GetText(TBStr &text) { return m_header.GetText(text); }
	using TBWidget::GetText; ///< Make all versions in base class available.

	virtual void SetValue(int value) { m_header.SetValue(value); m_toggle_container.SetValue(value); }
	virtual int GetValue() { return m_toggle_container.GetValue(); }

	virtual TBWidget *GetContentRoot() { return m_toggle_container.GetContentRoot(); }
private:
	TBLayout m_layout;
	TBSectionHeader m_header;
	TBToggleContainer m_toggle_container;
};

}; // namespace tinkerbell

#endif // TB_TOGGLE_CONTAINER_H