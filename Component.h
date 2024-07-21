#pragma once

class Component
{
public:
	// The lower the update order, the earlier the component updates
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:

	class Actor* mOwner;
	int mUpdateOrder;
};
