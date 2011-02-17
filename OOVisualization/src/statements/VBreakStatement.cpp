/***********************************************************************************************************************
 * VBreakStatement.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "statements/VBreakStatement.h"

#include "OOModel/headers/statements/BreakStatement.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VBreakStatement)

VBreakStatement::VBreakStatement(Item* parent, BreakStatement* node, const SymbolStyle* style) :
	ModelItem(parent, node, style),
	vis_(new Symbol(this, style))
{
}

VBreakStatement::~VBreakStatement()
{
	SAFE_DELETE_ITEM(vis_);
}

void VBreakStatement::determineChildren()
{
	vis_->setStyle( style());
}

void VBreakStatement::updateGeometry(int availableWidth, int availableHeight)
{
	Item::updateGeometry(vis_, availableWidth, availableHeight);
}

bool VBreakStatement::focusChild(FocusTarget location)
{
	return vis_->focusChild(location);
}

}