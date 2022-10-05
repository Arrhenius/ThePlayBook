/*
 * BaseWindow.h
 * 
 * This is the base class to all GUI windows 
 */


#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include "Helper.h"


class BaseWindow
{
public:

	BaseWindow();
	virtual ~BaseWindow();
	void	Disable();
	void	Enable();


	// getters
	bool	getIsActive();
	int		getHeight();
	int		getWidth();
	char*	getLabel();

	// setters
	void	setWidth(int width);
	void	setHeight(int height);
	void	setLabel(char* label);

private:
	int		m_width;
	int		m_height;
	bool	m_active;
	char	m_label[MAXLABELSZ + 1];

};


#endif // BASEWINDOW_H
