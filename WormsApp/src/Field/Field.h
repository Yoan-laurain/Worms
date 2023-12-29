#pragma once

#include "Objects/SActor.h"

class FieldPoint : public SActor 
{
	public:
		FieldPoint();

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