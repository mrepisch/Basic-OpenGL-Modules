#pragma once

// External includes
#include <vector>

// Internal includes
#include "System.h"


namespace component
{
	/**
	 * Class which holds all Systems in the application.
	 * So if you create a new System you have to add it in this class 
	 * Since the SystemCollection is just needed to be instanciated once it is 
	 * implemented as Singelton
	 * @author sascha blank
	 */
	class SystemCollection
	{
	public:
		
		/**
		 * Function to get a instance of this class
		 * SINGELTON PATTERN
		 * @author sascha blank
		 */
		static SystemCollection& Instance( void );

		/**
		 * virtual destructor
		 * @author sascha blank
		 */
		virtual ~SystemCollection( void );

		/**
		 * Add a new System to the system list
		 * @author sascha blank
		 */
		void addSystem( System* p_system );

		/**
		 * Update function which MUST be called in the mainloop
		 * @author sascha blank
		 */
		void update();

	private:

		/**
		 * Private constructor.
		 * SINGELTON PATTERN
		 * @author sascha blank
		 */
		SystemCollection() {}

		/**
		 * Private copy constructor
		 * @author sascha blank
		 */
		SystemCollection( const SystemCollection& t_other ) {}

		// Vector whith system
		std::vector<System*>m_systems;

		
	};
}
