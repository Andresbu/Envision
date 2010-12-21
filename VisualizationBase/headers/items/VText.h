/***********************************************************************************************************************
 * VText.h
 *
 *  Created on: Dec 14, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VTEXT_H_
#define VTEXT_H_

#include "visualizationbase_api.h"

#include "TextStyle.h"
#include "../ModelItem.h"
#include "ModelBase/headers/nodes/Text.h"
#include "VisualizationException.h"

#include <QtGui/QStaticText>

namespace Visualization {

class VISUALIZATIONBASE_API VText : public ModelItem
{
	ITEM_COMMON_CUSTOM_STYLENAME(VText, ModelItem, TextStyle)

	private:
		QStaticText text;

		qreal xOffset;
		qreal yOffset;

	public:
		VText(Item* parent, Model::Text *text, const TextStyle *style = NULL);

		virtual void determineChildren();
		virtual void updateState();

		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif /* VTEXT_H_ */