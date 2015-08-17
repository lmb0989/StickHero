#ifndef _TOUCHUTIL_H_
#define _TOUCHUTIL_H_

#include "cocos2d.h"
USING_NS_CC;

class TouchUtil
{
public:
	static bool isTouchInRect(Node* node, Touch* touch)
	{
		Point touchPointInNode = node->convertToNodeSpace(touch->getLocation());
		Size nodeSize = node->getContentSize();
		Rect rect = Rect(0, 0, nodeSize.width, nodeSize.height);
		if(rect.containsPoint(touchPointInNode))
		{
			return true;
		}
		return false;
	}

};

#endif