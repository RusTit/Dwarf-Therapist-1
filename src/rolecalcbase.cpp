#include "rolecalcbase.h"
#include <algorithm>
#include <QVector>

typedef QVector<double> VEC;
typedef VEC::iterator IT;
typedef VEC::const_iterator CIT;

RoleCalcBase::RoleCalcBase(const QVector<double> &sorted)
    : m_sorted(sorted)
    , m_count(0)
    , m_div(1)
{
    init_list();
}

RoleCalcBase::~RoleCalcBase(){
}

void RoleCalcBase::init_list(){
    m_begin = m_sorted.begin();
    m_end = m_sorted.end();
    m_count = static_cast<double>(m_sorted.size());
    m_div = m_count - 1.0;
    if(m_div == 0)
        m_div = 1;
}

double RoleCalcBase::pos_upper(double val)const{
    CIT it = qUpperBound(m_sorted,val);
    unsigned pos = it-m_begin;
    return pos-1;
}

double RoleCalcBase::pos_lower(double val)const{
    CIT it = qLowerBound(m_sorted,val);
    unsigned pos = it-m_begin;
    return pos;
}

double RoleCalcBase::rating(double val) {
    return base_rating(val) / 2.0f + 0.5;
}

double RoleCalcBase::base_rating(const double val){
    return ((pos_upper(val) + pos_lower(val)) / 2.0f) / m_div;
}

double RoleCalcBase::find_median(QVector<double> v){
    int idx_mid = (double)v.count() / 2.0f;
    double m = 0.0;
    if(v.count() % 2 == 0){
        std::nth_element(v.begin(),v.begin()+idx_mid,v.end());
        m = 0.5 * (v.at(idx_mid)+v.at(idx_mid-1));
    }else{
        std::nth_element(v.begin(),v.begin()+idx_mid,v.end());
        m =  v.at(idx_mid);
    }
    return m;
}

double RoleCalcBase::range_transform(double val, double min, double mid, double max){
    if(val <= mid){
        if(mid-min == 0){
            return 0;
        }else{
            return (val-min)/(mid-min)*0.5f;
        }
    }else{
        if(max-mid == 0){
            return mid;
        }else{
            return ((val-mid)/(max-mid)*0.5f)+0.5f;
        }
    }
}
