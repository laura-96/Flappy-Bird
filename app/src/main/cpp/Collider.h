//
// Created by Laura on 13/06/2018.
//

#ifndef FLAPPYBIRD_COLLIDER_H
#define FLAPPYBIRD_COLLIDER_H

enum CollisionType
{
    CIRCLE,
    TUBE,
    NONE
};

class Collider
{
	float x, y, w, h;

	float radius;
	CollisionType type;

	bool toDelete = false;

public:

	Collider();
	~Collider(){}

	Collider(float pos_x, float pos_y, float r);
	Collider(float pos_x, float pos_y, float width, float height);
	void SetToDelete();
	void Move(float move_x, float move_y);
	bool GetToDelete() const;
	bool CheckCollision(Collider* col) const;
	const CollisionType GetType() const;

};
#endif //FLAPPYBIRD_COLLIDER_H
