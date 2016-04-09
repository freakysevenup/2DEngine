#pragma once

class Reference
{
public:
	Reference() : m_referenceCount(1) {}

	inline void addReference() { m_referenceCount++; }
	inline bool removeReference() { m_referenceCount--; return m_referenceCount == 0; }
	inline unsigned int getReferenceCount() { return m_referenceCount; }

private:
	unsigned int m_referenceCount;
};