#include "runtime/resource/res_type/components/camera.h"

#include "runtime/core/base/macro.h"

namespace Movan
{
    CameraComponentRes::CameraComponentRes(const CameraComponentRes& res)
    {
        const std::string& camera_type_name = res.m_parameter.getTypeName();
        if (camera_type_name == "FirstPersonCameraParameter")
        {
            m_parameter = MOVAN_REFLECTION_NEW(FirstPersonCameraParameter);
            MOVAN_REFLECTION_DEEP_COPY(FirstPersonCameraParameter, m_parameter, res.m_parameter);
        }
        else if (camera_type_name == "ThirdPersonCameraParameter")
        {
            m_parameter = MOVAN_REFLECTION_NEW(ThirdPersonCameraParameter);
            MOVAN_REFLECTION_DEEP_COPY(ThirdPersonCameraParameter, m_parameter, res.m_parameter);
        }
        else if (camera_type_name == "FreeCameraParameter")
        {
            m_parameter = MOVAN_REFLECTION_NEW(FreeCameraParameter);
            MOVAN_REFLECTION_DEEP_COPY(FreeCameraParameter, m_parameter, res.m_parameter);
        }
        else
        {
            LOG_ERROR("invalid camera type");
        }
    }

    CameraComponentRes::~CameraComponentRes() { MOVAN_REFLECTION_DELETE(m_parameter); }
} // namespace Movan