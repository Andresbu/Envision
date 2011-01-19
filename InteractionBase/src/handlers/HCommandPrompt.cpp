/***********************************************************************************************************************
 * HCommandPrompt.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "handlers/HCommandPrompt.h"

#include "vis/CommandPrompt.h"
#include "commands/CommandExecutionEngine.h"
#include "commands/CommandResult.h"

#include "VisualizationBase/headers/Scene.h"

#include <QtCore/QtDebug>

namespace Interaction {

HCommandPrompt::HCommandPrompt()
{
}

HCommandPrompt* HCommandPrompt::instance()
{
	static HCommandPrompt h;
	return &h;
}

void HCommandPrompt::keyReleaseEvent(Visualization::Item *target, QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		CommandPrompt* prompt = static_cast<CommandPrompt*> (target);
		qDebug() << prompt->text();
		prompt->commandReceiver()->execute(prompt->text());

		CommandResult* result = executionEngine()->result();

		if ( result->code() == CommandResult::OK)
		{

		}
		else
		{
			prompt->setSuggestions(result->suggestions());
			prompt->setErrors(result->errors());
			prompt->scene()->updateTopLevelItems();
		}
	}
	else GenericHandler::keyReleaseEvent(target, event);
}

}