#include "BaseWindow.h"
#include <string.h>
#include <stdio.h>



BaseWindow::BaseWindow()
{
	m_width = 0;
	m_height = 0;
	m_active = false;
	memset(m_label, 0, sizeof(m_label));
}


BaseWindow::~BaseWindow()
{
	memset(m_label, 0, sizeof(m_label));
}

void BaseWindow::Disable()
{
	m_active = false;
}

void BaseWindow::Enable()
{
	m_active = true;
}

bool BaseWindow::getIsActive()
{
	return m_active;
}

int BaseWindow::getHeight()
{
	return m_height;
}

int BaseWindow::getWidth()
{
	return m_width;
}

char* BaseWindow::getLabel()
{
	return m_label;
}

void BaseWindow::setWidth(int width)
{
	m_width = width;
}

void BaseWindow::setHeight(int height)
{
	m_height = height;
}

void BaseWindow::setLabel(char* label)
{
	size_t len = strlen(label);

	if (len <= MAXLABELSZ && *label)
		strcpy(m_label, label);
	else if (len > MAXLABELSZ)
	{
		fprintf(stderr, "Label string provided exceeded max size!\n");
		fprintf(stderr, "Proceeding with no label associated to window\n");
		m_label[0] = '\0';
		return;
	}
	else if (*label == '\0' || *label == '\n')
		m_label[0] = '\0';
	return;
}

