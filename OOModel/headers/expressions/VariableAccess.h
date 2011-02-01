/***********************************************************************************************************************
 * VariableAccess.h
 *
 *  Created on: Jan 31, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VARIABLEACCESS_H_
#define VARIABLEACCESS_H_

#include "Expression.h"
#include "../OOReference.h"

namespace OOModel {

class OOMODEL_API VariableAccess: public Expression
{
	EXTENDABLENODE_DECLARE_STANDARD_METHODS(VariableAccess)

	ATTRIBUTE(Expression, prefix)
	ATTRIBUTE(OOReference, ref)
};

}

#endif /* VARIABLEACCESS_H_ */