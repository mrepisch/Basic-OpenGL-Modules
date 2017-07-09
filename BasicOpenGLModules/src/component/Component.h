#pragma once

namespace component
{
	enum EnComponents
	{
		e_undefinedComponent = 0,
		e_renderComponent,
		e_positionComponent,
		e_cameraComponent
	};

	/**
	 * This is the interface which shoud be used for implementing components.
	 * Every component needs to have a entry in the EnComponents enum.
	 * @author sascha blank
	 */
	class Component
	{
	public:
		Component() {};

		EnComponents getComponentType() { return m_componentType; }
			
	protected:
		EnComponents m_componentType;

	};
}
