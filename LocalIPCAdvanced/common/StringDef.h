#pragma once

#include <QString>

namespace PacketType
{
const QString UNKNOWN_PACKET = "UnknownPacket";
const QString FRAME = "Frame";
const QString REQUEST = "Request";
const QString REPLY = "Reply";
const QString COMMAND = "Command";
}

namespace DaqcParameter
{
const QString REGION_PHYSICAL_DELTA_X = "RegionPhysicalDeltaX";
const QString REGION_PHYSICAL_DELTA_Y = "RegionPhysicalDeltaY";
const QString B_GAIN = "BGain";
const QString B_GAIN2 = "BGain2";
const QString C_GAIN = "CGain";
const QString XML_DEPTH = "XmlDepth";
const QString DEPTH_MM = "DepthMm";
const QString DEPTH_CM = "DepthCm";
const QString B_FREQUENCY = "BFrequency";
const QString B_FREQUENCY_2 = "BFrequency2";
const QString CHROMA = "Chroma";
const QString IMG_PROC = "ImgProc";
const QString FAVG = "Favg";
const QString LAVG = "Lavg";
const QString CONTRAST = "Contrast";
const QString C_PRF = "CPrf";
const QString D_PRF = "DPrf";
const QString C_WF = "CWF";
const QString D_WF = "DWF";
const QString SENSITIVITY = "Sensitivity";
const QString SWING_ANGLE = "SwingAngle";
const QString SV = "Sv";
const QString CA = "Ca";
const QString D_SPEED = "DSpeed";
const QString M_SPEED = "MSpeed";
const QString NOISE_REJECT = "NoiseReject";
const QString AUDIO = "Audio";
const QString DEPTH = "Depth";
const QString ROI_SITE = "RoiSite";
const QString ROI_SIZE = "RoiSize";
const QString C_AUTO_TRACE = "CAutoTrace";
const QString D_AUTO_TRACE = "DAutoTrace";
const QString UPDATE = "Update";
const QString SYNCHRO = "Synchro";
const QString DUAL_MODE = "DualMode";
const QString ACUI = "Acui";
const QString A_POWER = "APower";
const QString ANATOMY_LINE = "AnatomyLine";
const QString B_C_D_SYNCHRO = "BCDSynChro";
const QString B_DYNAMIC = "BDynamic";
const QString B_NOISE_REJECTION = "BNoiseRejection";
const QString C_BASE_LINE = "CBaseLine";
const QString C_DYNAMIC = "CDynamic";
const QString C_FREQUENCY = "CFrequency";
const QString C_NOISE_REJECTION = "CNoiseRejection";
const QString C_WALL_FILTER_FREQ = "CWallFilterFreq";
const QString COLOR_INVERT = "ColorInvert";
const QString D_INVERT = "DInvert";
const QString COLOR_PRIOR = "ColorPrior";
const QString CWD_GAIN = "CwdGain";
const QString D_BASELINE = "DBaseLine";
const QString D_DYNAMIC = "DDynamic";
const QString D_NOISE_REJECTION = "DNoiseRejection";
const QString D_SOUND_VOLUME = "DSoundVolume";
const QString D_WALL_FILTER_FREQ = "DWallFilterFreq";
const QString DIR_PWR_GAIN = "DirPwrGain";
const QString DSC_CAPTURE = "DscCapture";
const QString EXAM_TYPE_ID = "ExamTypeID";
const QString FRAME_RELATION = "FrameRelation";
const QString INIT = "Init";
const QString F_PROBE_TYPE = "FProbeType";
const QString IMAGE_PROCESS = "ImageProcess";
const QString PROBE_INFO = "ProbeInfo";
const QString PROBE_POS = "ProbePOS";
const QString RADIUM = "Radium";
const QString ESPIN = "ESpin";
const QString PWIF_BUFF_MS = "PwifBuffms";
const QString SCAN_MODE = "ScanMode";
const QString REALTIME_EN = "RealtimeEn";
const QString START = "Start";
const QString STOP = "Stop";
const QString THI = "THI";
const QString ZOOM_COLOR_ROI = "ZoomColorROI";
const QString MOVE_ROI_COLOR = "MoveROIColor";
const QString TGC_POSITIONS = "TGCPositions";
const QString GET_PARAMETER = "GetParameter";
const QString PERSISTENCE_COLOR = "PersistenceColor";
const QString PROBE_SEL = "ProbeSEL";
const QString FLIP_H = "FlipH";
const QString FLIP_V = "FlipV";
}