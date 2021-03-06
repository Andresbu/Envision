/***********************************************************************************************************************
**
** Copyright (c) 2011, ETH Zurich
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
** following conditions are met:
**
**    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
**      disclaimer.
**    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
**      following disclaimer in the documentation and/or other materials provided with the distribution.
**    * Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products
**      derived from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
***********************************************************************************************************************/

/***********************************************************************************************************************
 * SimpleTest.cpp
 *
 *  Created on: Mar 24, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "custommethodcall.h"
#include "SelfTest/src/SelfTestSuite.h"

#include "CustomVisualization.h"

#include "OOModel/src/allOOModelNodes.h"

#include "VisualizationBase/src/node_extensions/Position.h"
#include "VisualizationBase/src/Scene.h"
#include "VisualizationBase/src/views/MainView.h"

using namespace OOModel;
using namespace Visualization;

namespace CustomMethodCall {

Class* addCollection(Model::Model* model, Project* parent)
{
	Class* col = nullptr;

	if (!parent) col = dynamic_cast<Class*> (model->createRoot("Class"));
	model->beginModification(parent ? static_cast<Model::Node*> (parent) :col, "Adding a collection class.");
	if (!col)
	{
		col = new Class();
		parent->classes()->append(col);
	}

	col->setName("Collection");
	col->setVisibility(Visibility::PUBLIC);

	Method* find = new Method();
	col->methods()->append(find);
	find->setName("find");
	find->extension<CustomVisualization>()->setVisName("FindMethodVis");
	FormalArgument* findArg = new FormalArgument();
	find->arguments()->append(findArg);
	findArg->setType(new PrimitiveType(PrimitiveType::INT));
	findArg->setName("x");
	FormalResult* findResult = new FormalResult();
	findResult->setType(new PrimitiveType(PrimitiveType::INT));
	find->results()->append(findResult);

	Method* insert = new Method();
	col->methods()->append(insert);
	insert->setName("insert");
	insert->extension<CustomVisualization>()->setVisName("InsertMethodVis");
	insert->extension<Position>()->setY(100);
	FormalArgument* insertArg = new FormalArgument();
	insert->arguments()->append(insertArg);
	insertArg->setType(new PrimitiveType(PrimitiveType::INT));
	insertArg->setName("x");

	Method* empty = new Method();
	col->methods()->append(empty);
	empty->setName("empty");
	empty->extension<CustomVisualization>()->setVisName("EmptyMethodVis");
	empty->extension<Position>()->setY(200);
	FormalResult* emptyResult = new FormalResult();
	emptyResult->setType(new PrimitiveType(PrimitiveType::BOOLEAN));
	empty->results()->append(emptyResult);

	Method* exists = new Method();
	col->methods()->append(exists);
	exists->setName(QChar(0x2203));
	exists->extension<CustomVisualization>()->setVisName("ExistsMethodVis");
	exists->extension<Position>()->setY(300);
	FormalArgument* existsArg = new FormalArgument();
	exists->arguments()->append(existsArg);
	existsArg->setType(new PrimitiveType(PrimitiveType::INT));
	existsArg->setName("x");
	FormalResult* existsResult = new FormalResult();
	existsResult->setType(new PrimitiveType(PrimitiveType::BOOLEAN));
	exists->results()->append(existsResult);

	Method* sum = new Method();
	col->methods()->append(sum);
	sum->setName("sum");
	sum->extension<CustomVisualization>()->setVisName("SumMethodVis");
	sum->extension<Position>()->setY(400);
	FormalArgument* sumArgFrom = new FormalArgument();
	sum->arguments()->append(sumArgFrom);
	sumArgFrom->setType(new PrimitiveType(PrimitiveType::INT));
	sumArgFrom->setName("from");
	FormalArgument* sumArgTo = new FormalArgument();
	sum->arguments()->append(sumArgTo);
	sumArgTo->setType(new PrimitiveType(PrimitiveType::INT));
	sumArgTo->setName("to");
	FormalResult* sumResult = new FormalResult();
	sumResult->setType(new PrimitiveType(PrimitiveType::INT));
	sum->results()->append(sumResult);

	Method* test = new Method();
	col->methods()->append(test);
	test->setName("test");
	test->extension<Position>()->setX(300);

	IfStatement* ifs = new IfStatement();
	test->items()->append(ifs);
	BinaryOperation* orIf = new BinaryOperation();
	ifs->setCondition(orIf);
	orIf->setOp(BinaryOperation::CONDITIONAL_OR);
	MethodCallExpression* emptyCall = new MethodCallExpression();
	orIf->setLeft(emptyCall);
	emptyCall->ref()->set("method:empty");

	UnaryOperation* negation = new UnaryOperation();
	orIf->setRight(negation);
	negation->setOp(UnaryOperation::NOT);
	MethodCallExpression* existsCall = new MethodCallExpression();
	negation->setOperand(existsCall);
	existsCall->ref()->set(QString("method:%1").arg(QChar(0x2203)));
	existsCall->arguments()->append( new IntegerLiteral(42));

	ExpressionStatement* insertCallSt = new ExpressionStatement();
	MethodCallExpression* insertCall = new MethodCallExpression();
	insertCall->ref()->set("method:insert");
	insertCall->arguments()->append( new IntegerLiteral(42));
	insertCallSt->setExpression(insertCall);
	ifs->thenBranch()->append(insertCallSt);

	VariableDeclaration* indexVar = new VariableDeclaration();
	test->items()->append(new ExpressionStatement(indexVar));
	indexVar->setName("index");
	indexVar->setType(new PrimitiveType(PrimitiveType::INT));
	MethodCallExpression* findCall = new MethodCallExpression();
	indexVar->setInitialValue(findCall);
	findCall->ref()->set("method:find");
	findCall->arguments()->append( new IntegerLiteral(42));

	VariableDeclaration* resultVar = new VariableDeclaration();
	test->items()->append(new ExpressionStatement(resultVar));
	resultVar->setName("result");
	resultVar->setType(new PrimitiveType(PrimitiveType::INT));
	MethodCallExpression* sumCall = new MethodCallExpression();
	resultVar->setInitialValue(sumCall);
	sumCall->ref()->set("method:sum");
	sumCall->arguments()->append( new IntegerLiteral(0));
	sumCall->arguments()->append( new VariableAccess("local:index"));
	sumCall->setPrefix(new ThisExpression());

	ReturnStatement* testReturn = new ReturnStatement();
	testReturn->values()->append(new VariableAccess("local:result"));
	test->items()->append(testReturn);

	FormalResult* testFormalResult = new FormalResult();
	testFormalResult->setType(new PrimitiveType(PrimitiveType::INT));
	test->results()->append(testFormalResult);

	model->endModification();
	return col;
}

TEST(CustomMethodCall, CustomVisTest)
{
	Scene* scene = new Scene();

	////////////////////////////////////////////////// Create Model
	Model::Model* model = new Model::Model();

	Class* collection = nullptr;
	collection = addCollection(model, nullptr);

	////////////////////////////////////////////////// Set Scene
	Model::Node* top_level = nullptr;
	if(collection) top_level = collection;

	scene->addTopLevelItem( scene->defaultRenderer()->render(nullptr, top_level) );
	scene->scheduleUpdate();
	scene->listenToModel(model);

	// Create view
	MainView* view = new MainView(scene);

	CHECK_CONDITION(view != nullptr);
}

}
