#ifndef IPL_MATH_INTERPORATION_H
#define IPL_MATH_INTERPORATION_H

#ifdef __cplusplus

#include <nw4r/math.h>

#include "utility/iplFrameController.h"

#ifdef IPL_GC_WINDOW_CPP
#include "math/iplMathTypes.h"
#endif

#ifdef IPL_GCW_INTP_CTOR_OUT_OF_LINE
#include "global/decomp/utils.h"
#endif

namespace ipl {
    namespace math {
        template <typename T>
        class Interporation : public utility::FrameController {
        public:
#ifdef IPL_BOARD_OBJECT_INLINE_INTERPOLATION_DTORS
            virtual ~Interporation();
#endif
            void init(int playback, f32 maxFrame, f32 minFrame, const T& start, const T& end, f32 speed = 1.0f) {
                mStart = start;
                mEnd = end;
                utility::FrameController::init(playback, maxFrame, minFrame, speed);
            }

            const T& getStart() { return mStart; }
            const T& getEnd() { return mEnd; }

            void playBackwards() {
                mAnmType = ANIM_TYPE_BACKWARD;
                mState = ANIM_STATE_PLAY;
            }

        protected:
            T mStart;
            T mEnd;
        };

#ifdef IPL_GC_WINDOW_CPP
        template <>
        class Interporation<VEC3> : public utility::FrameController {
        public:
            virtual ~Interporation();

            void init(int playback, f32 maxFrame, f32 minFrame, const VEC3& start,
                      const VEC3& end, f32 speed = 1.0f) {
                mStart = start;
                mEnd = end;
                utility::FrameController::init(playback, maxFrame, minFrame, speed);
            }

            const VEC3& getStart() { return mStart; }
            const VEC3& getEnd() { return mEnd; }

            void playBackwards() {
                mAnmType = ANIM_TYPE_BACKWARD;
                mState = ANIM_STATE_PLAY;
            }

        protected:
            VEC3 mStart;
            VEC3 mEnd;
        };
#endif

        template <typename T>
        class LinearIntp : public Interporation<T> {
        public:
#ifdef IPL_GCW_INTP_CTOR_OUT_OF_LINE
            LinearIntp() NO_INLINE;
#endif
#if defined(IPL_BOARD_OBJECT_INLINE_INTERPOLATION_DTORS) || defined(IPL_GC_WINDOW_CPP)
            virtual ~LinearIntp();
#endif
#ifdef IPL_GC_WINDOW_CPP
            T get() const;
#else
            T get() const {
                T r = mEnd * getCurrentFrame();
                T b = mStart * (mMaxFrame - mFrame);
                b += r;
                return b * (f64)(1.0f / getMaxFrame());
            }

#endif
            T get2() const { return (((mStart * (mMaxFrame - mFrame)) + (mEnd * mFrame)) / mMaxFrame); }
        };

#ifdef IPL_GC_WINDOW_CPP
        template <>
        class LinearIntp<VEC3> : public Interporation<VEC3> {
        public:
            LinearIntp();
            virtual ~LinearIntp();
            VEC3 get() const;
        };
#endif


#ifdef IPL_CHANNEL_TITLE_NOVTABLE
        template <typename T>
        class __declspec(novtable) HermiteIntp : public utility::FrameController {
        public:
            HermiteIntp() {}
            virtual ~HermiteIntp();

            void init(const T& start, const T& end, f32 maxFrame, f32 startTangent, f32 endTangent, int playback = ANIM_TYPE_FORWARD, f32 speed = 1.0f);

            T get() const {
                f32 var_f27 = mFrame;
                f32 var_f28 = 1.0f / mMaxFrame;
                T r =
                    (mStart *
                     (1.0f + ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                              (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))))) -
                    (mEnd * ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                              (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))));
                r +=
                    (mStartTangent *
                     (var_f27 +
                      ((var_f28 * (var_f28 * (var_f27 * (var_f27 * var_f27)))) -
                       (var_f28 * (2.0f * var_f27 * var_f27))))) +
                    (mEndTangent * ((var_f28 * (var_f28 * (var_f27 * (var_f27 * var_f27)))) -
                                (var_f28 * (var_f27 * var_f27))));

                return r;

                /*f32 var_f27 = mMaxFrame;
                f32 var_f28 = 1.0f / mMaxFrame;
                T sp28 = mEnd * ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                                 (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27))));
                T sp1C = mStart * (1.0f + ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                                           (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))));
                T r = sp1C - sp28;

                f32 temp_f4 = var_f27 * var_f27;
                f32 temp_f7 = var_f28 * (var_f28 * (var_f27 * temp_f4));
                f32 temp_f3 =
                    (mStartTangent * (var_f27 + (temp_f7 - (var_f28 * (2.0f * var_f27 * var_f27))))) + (mEndTangent * (temp_f7 - (var_f28 * temp_f4)));
                r = r + temp_f3;
                return r;*/
            }

        protected:
            T mStart;
            T mEnd;
            f32 mStartTangent;
            f32 mEndTangent;
        };

        template <>
        class HermiteIntp<f32> : public utility::FrameController {
        public:
            HermiteIntp() {}
            virtual ~HermiteIntp();

            void init(const f32& start, const f32& end, f32 maxFrame, f32 startTangent, f32 endTangent, int playback = ANIM_TYPE_FORWARD,
                      f32 speed = 1.0f);

            f32 get() const {
                f32 var_f27 = mFrame;
                f32 var_f28 = 1.0f / mMaxFrame;
                f32 r =
                    (mStart *
                     (1.0f + ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                              (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))))) -
                    (mEnd * ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                              (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))));
                r +=
                    (mStartTangent *
                     (var_f27 + ((var_f28 * (var_f28 * (var_f27 * (var_f27 * var_f27)))) -
                                 (var_f28 * (2.0f * var_f27 * var_f27))))) +
                    (mEndTangent * ((var_f28 * (var_f28 * (var_f27 * (var_f27 * var_f27)))) -
                                (var_f28 * (var_f27 * var_f27))));

                return r;
            }

        protected:
            f32 mStart;
            f32 mEnd;
            f32 mStartTangent;
            f32 mEndTangent;
        };

#pragma dont_instantiate HermiteIntp<float>
#else
        template <typename T>
        class HermiteIntp : public Interporation<T> {
        public:
            HermiteIntp() {}

            void init(const T& start, const T& end, f32 maxFrame, f32 startTangent, f32 endTangent, int playback = ANIM_TYPE_FORWARD, f32 speed = 1.0f) {
                mStart = start;
                mEnd = end;
                utility::FrameController::init(playback, maxFrame, 0.0f, speed);
                mStartTangent = startTangent;
                mEndTangent = endTangent;
            }

#ifdef IPL_SD_CHANNEL_SELECT_CPP
            T get() const {
                f32 frame = mFrame;
                f32 inverseDuration = 1.0f / mMaxFrame;
                T result =
                    (mStart * (1.0f + (inverseDuration * (inverseDuration *
                        (inverseDuration * (frame * (2.0f * frame * frame)))) -
                        inverseDuration * (inverseDuration * (3.0f * frame * frame))))) -
                    (mEnd * (inverseDuration * (inverseDuration *
                        (inverseDuration * (frame * (2.0f * frame * frame)))) -
                        inverseDuration * (inverseDuration * (3.0f * frame * frame))));
                f32 frameSquared = frame * frame;
                f32 cubic = inverseDuration * (inverseDuration * (frame * frameSquared));
                f32 tangent = mStartTangent * (frame + (cubic -
                    inverseDuration * (2.0f * frame * frame))) +
                    mEndTangent * (cubic - inverseDuration * frameSquared);
                result.x += tangent;
                result.y += tangent;
                result.z += tangent;
                return result;
            }
#else
            T get() const {
                f32 var_f27 = mFrame;
                f32 var_f28 = 1.0f / mMaxFrame;
                f32 t1t2 =
                    (var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) - (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)));

                T r = (mStart * (1.0f + t1t2)) - (mEnd * t1t2);

                f32 temp_f4 = var_f27 * var_f27;
                f32 temp_f7 = var_f28 * (var_f28 * (var_f27 * temp_f4));
                f32 temp_f3 =
                    (mStartTangent * (var_f27 + (temp_f7 - (var_f28 * (2.0f * var_f27 * var_f27))))) + (mEndTangent * (temp_f7 - (var_f28 * temp_f4)));

                r = r + temp_f3;

                return r;

                /*f32 var_f27 = mMaxFrame;
                f32 var_f28 = 1.0f / mMaxFrame;
                T sp28 = mEnd * ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                                 (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27))));
                T sp1C = mStart * (1.0f + ((var_f28 * (var_f28 * (var_f28 * (var_f27 * (2.0f * var_f27 * var_f27))))) -
                                           (var_f28 * (var_f28 * (3.0f * var_f27 * var_f27)))));
                T r = sp1C - sp28;

                f32 temp_f4 = var_f27 * var_f27;
                f32 temp_f7 = var_f28 * (var_f28 * (var_f27 * temp_f4));
                f32 temp_f3 =
                    (mStartTangent * (var_f27 + (temp_f7 - (var_f28 * (2.0f * var_f27 * var_f27))))) + (mEndTangent * (temp_f7 - (var_f28 * temp_f4)));
                r = r + temp_f3;
                return r;*/
            }
#endif

        protected:
            f32 mStartTangent;
            f32 mEndTangent;
        };
#endif

#ifdef IPL_SD_CHANNEL_SELECT_CPP
}  // namespace math
}  // namespace ipl
#include "math/iplMathTypes.h"
namespace ipl {
    namespace math {
        template <>
        class HermiteIntp<VEC3> : public utility::FrameController {
        public:
            HermiteIntp() {}
            virtual ~HermiteIntp();
            void init(const VEC3& start, const VEC3& end, f32 maxFrame, f32 startTangent, f32 endTangent, int playback = ANIM_TYPE_FORWARD, f32 speed = 1.0f);
            VEC3 get() const {
                f32 frame = mFrame;
                f32 inverseDuration = 1.0f / mMaxFrame;
                VEC3 result =
                    (mStart * (1.0f + (inverseDuration * (inverseDuration *
                        (inverseDuration * (frame * (2.0f * frame * frame)))) -
                        inverseDuration * (inverseDuration * (3.0f * frame * frame))))) -
                    (mEnd * (inverseDuration * (inverseDuration *
                        (inverseDuration * (frame * (2.0f * frame * frame)))) -
                        inverseDuration * (inverseDuration * (3.0f * frame * frame))));
                f32 frameSquared = frame * frame;
                f32 cubic = inverseDuration * (inverseDuration * (frame * frameSquared));
                f32 tangent = mStartTangent * (frame + (cubic -
                    inverseDuration * (2.0f * frame * frame))) +
                    mEndTangent * (cubic - inverseDuration * frameSquared);
                result.x += tangent;
                result.y += tangent;
                result.z += tangent;
                return result;
            }
        protected:
            VEC3 mStart;
            VEC3 mEnd;
            f32 mStartTangent;
            f32 mEndTangent;
        };
#endif

    }  // namespace math
}  // namespace ipl

#endif  // __cplusplus

#endif  // IPL_MATH_INTERPORATION_H
