#ifndef _ROS_counter_Person_h
#define _ROS_counter_Person_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace counter
{

  class Person : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef int32_t _points_type;
      _points_type points;

    Person():
      name(""),
      points(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      union {
        int32_t real;
        uint32_t base;
      } u_points;
      u_points.real = this->points;
      *(outbuffer + offset + 0) = (u_points.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_points.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_points.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_points.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->points);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      union {
        int32_t real;
        uint32_t base;
      } u_points;
      u_points.base = 0;
      u_points.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_points.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_points.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_points.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->points = u_points.real;
      offset += sizeof(this->points);
     return offset;
    }

    const char * getType(){ return "counter/Person"; };
    const char * getMD5(){ return "4b304fb8328d2d8f339094361a76d13c"; };

  };

}
#endif