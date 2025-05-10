/*
 * PCM1809_AudioInputDevice.hpp
 *
 *  Created on: Apr 2, 2025
 *      Author: Alex
 */

#ifndef INC_VMB_PCM1809_AUDIOINPUTDEVICE_HPP_
#define INC_VMB_PCM1809_AUDIOINPUTDEVICE_HPP_

#include "IAudioInputDevice.hpp"

namespace VMB
{
	class PCM1809_AudioInputDevice : public IAudioInputDevice
	{
	public:


		void startCaptureAudio() override;
		void stopCaptureAudio() override;

	private:

	};

}
#endif /* INC_VMB_PCM1809_AUDIOINPUTDEVICE_HPP_ */
