#pragma once
#include "Decision.h"
#include "Condition.h"

class BooleanDecision : public Decision
{
public:

    BooleanDecision(Decision* a, Decision* b, Condition* condition)
        : m_a(a), m_b(b), m_condition(condition) {}

    ~BooleanDecision() {}

    virtual void makeDecision(Agent* agent, float deltaTime);

private:
    Decision* m_a;
    Decision* m_b;
    Condition* m_condition;


};

