#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP
/**
 * @author Alex Krieg
 */

#include <vector>

namespace VoiceMailBox
{
	/**
	 * @brief This class is used for objects that need to be updated periodically.
	 *        This class collects all instances that are updatable. All objects can be updated
	 *        easyaly by calling the static function updateInstances().
	 */
	class Updatable
	{
	public:
		Updatable();
		virtual ~Updatable();

		/**
		 * @brief Updates the object
		 * @details This function is called periodically to update the object.
		 */
		virtual void update() = 0;


		/**
		 * @brief Updates all object instances that derived from this class.
		 */
		static void updateInstances();
	private:

		static std::vector<Updatable*> &getInstances();
	};
}
#endif
