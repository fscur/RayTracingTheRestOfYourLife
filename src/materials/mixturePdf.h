#pragma once
#include "pdf.h"

class mixturePdf :
    public pdf 
{
public:
    mixturePdf(pdf* pdf0, pdf* pdf1);

    virtual float value(const vec3& direction) const override;
    virtual vec3 generate() const override;

private:
    pdf* _pdfs[2];
};