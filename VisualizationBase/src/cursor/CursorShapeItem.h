/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2012 ETH Zurich
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 ** following conditions are met:
 **
 **    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 **      following disclaimer.
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
 **********************************************************************************************************************/

/*
 * CursorShapeItem.h
 *
 *  Created on: Jan 26, 2012
 *      Author: Dimitar Asenov
 */

#ifndef VisualizationBase_CURSORSHAPEITEM_H_
#define VisualizationBase_CURSORSHAPEITEM_H_

#include "../visualizationbase_api.h"
#include "../items/ItemStyle.h"
#include "../items/Item.h"

namespace Visualization {

class VISUALIZATIONBASE_API CursorShapeItem: public Item
{
	ITEM_COMMON_CUSTOM_STYLENAME(CursorShapeItem, ItemStyle)

	public:
		CursorShapeItem(const StyleType* style = itemStyles().get());
		virtual ~CursorShapeItem();

		virtual bool needsUpdate();
		void setCursorSize(const QSize& size);
		void setCursorCenter(const QPoint& center);
		void setCursorTopLeft(const QPoint& topLeft);

	protected:
		virtual void determineChildren();
		virtual void updateGeometry(int availableWidth, int availableHeight);

	private:
		bool useCenter_;
		QSize size_;
		QPoint center_;
		QPoint topLeft_;
};

inline void CursorShapeItem::setCursorSize(const QSize& size) { size_ = size; }
inline void CursorShapeItem::setCursorCenter(const QPoint& center) { center_ = center; useCenter_=true;}
inline void CursorShapeItem::setCursorTopLeft(const QPoint& topLeft) { topLeft_ = topLeft; useCenter_=false;}

} /* namespace Visualization */
#endif /* VisualizationBase_CURSORSHAPEITEM_H_ */
