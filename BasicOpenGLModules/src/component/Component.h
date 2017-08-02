#pragma once

namespace component
{
	enum EnComponents
	{
		e_undefinedComponent = 0,
		e_renderComponent,
		e_translationComponent,
		e_cameraComponent,
		e_lightningComponent,
		e_cubemapComponent
	};

	/**
	 * This is the interface which shoud be used for implementing components.
	 * Every component needs to have a entry in the EnComponents enum.
	 * @author sascha blank
	 */
	class Component
	{
	public:

		/**
		 * Constructor
		 * @author sascha blank
		 * @EnComponents component type enum
		 */
		Component(EnComponents p_component) { m_componentType = p_component; };

		/**
		 * Function to return the component type
		 */
		EnComponents getComponentType() { return m_componentType; }
			
	protected:

		// Component type enum
		EnComponents m_componentType;

	};
}
