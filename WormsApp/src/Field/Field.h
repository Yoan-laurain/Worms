#pragma once

#include "Object/SActor.h"

class FieldPoint : public SActor 
{
	public:
		FieldPoint(float x, float y);
		FieldPoint() = default;

	protected:
		void OnCollide(SActor* pActor);
};

class Field : public SActor
{
	public : 

		Field();

		void GenerateFieldCurve();

	private :
		std::vector<std::unique_ptr<FieldPoint>> m_FieldPoint;
};