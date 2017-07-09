#pragma once
namespace render 
{
	/**
	 * This interface is uses to define the interface from the Mesh to the uses rendering technology.
	 * @author
	 */
	class IMeshRender
	{
		/**
		 * Function to setup the mesh if needed
		 */
		virtual void init() = 0;

		/**
		 * Function to be called in the main loop
		 */
		virtual void render() = 0;
	};
}