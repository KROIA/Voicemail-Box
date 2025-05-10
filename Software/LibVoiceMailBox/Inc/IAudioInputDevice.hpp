/*
 * IAudioInputDevice.hpp
 *
 *  Created on: Apr 2, 2025
 *      Author: Alex
 */

#ifndef IAUDIOINPUTDEVICE_HPP_
#define IAUDIOINPUTDEVICE_HPP_

#include "IFile.hpp"

namespace VMB
{
	class IAudioInputDevice
	{
	public:
		IAudioInputDevice()
			: m_fileReceiver(nullptr)
		{}
		virtual ~IAudioInputDevice() = default;


		void setFileReceiver(IFile &file){ m_fileReceiver = &file; }
		IFile* getFileReceiver() const { return m_fileReceiver; }

		virtual void startCaptureAudio() = 0;
		virtual void stopCaptureAudio() = 0;


	protected:

		IFile *m_fileReceiver;

	};
}
#endif /* IAUDIOINPUTDEVICE_HPP_ */
