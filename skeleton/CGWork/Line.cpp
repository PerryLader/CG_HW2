#include "Line.h"




Line::Line(const Vector3& a, const Vector3& b, ColorGC color): m_a(a), m_b(b), m_color(color) {}
// Calculate the direction vector of the line
Vector3 Line::direction() const {
    return (m_b - m_a).normalized();
}

Line Line::getTransformedLine(const Matrix4& transformation) const
{
    
    return Line((transformation * Vector4::extendOne(m_a)).toVector3(),
        (transformation * Vector4::extendOne(m_b)).toVector3(),
        m_color);
}

// Calculate the length of the line
float Line::length() const {
    return (m_b - m_a).length();
}

// Check if two lines intersect, and return the intersection point if they do
bool Line::findIntersection(const Line& line1, const Line& line2, Vector3& interVector) {
    
    double epsilon = 0.005;
    Vector3 crossD1D2 = Vector3::cross(line1.m_b,line2.m_b);
    double crossNorm = crossD1D2.normalized().length();

    // Check if the lines are parallel
    if (crossNorm < epsilon) {
        // Check if the lines are collinear
        Vector3 P2P1 = line2.m_a - line1.m_a;
        if (Vector3::cross(line1.m_b,P2P1).normalized().length() < epsilon) {
            throw ; // Lines are collinear
        }
        throw; // Lines are parallel but not intersecting
    }

    // Compute the intersection parameters t and s
    Vector3 P2P1 = line1.m_a - line2.m_a;
    double t = Vector3::dot(Vector3::cross(P2P1,line2.m_b),crossD1D2) / Vector3::dot(crossD1D2,crossD1D2);
    double s = Vector3::dot(Vector3::cross(P2P1,line1.m_b),crossD1D2) / Vector3::dot(crossD1D2,crossD1D2);

    // Intersection point
    Vector3 intersection1 = line1.m_a + line1.m_b * t;
    Vector3 intersection2 = line2.m_a + line2.m_b * s;

    // Verify if the intersection points match
    if ((intersection1 - intersection2).normalized().length() < epsilon) {
        interVector = intersection1;
        return true; // The lines intersect
    }

    return false; // The lines are skew (not intersecting)
}

bool Line::clip(Line& newLine)
{
    bool v1In = m_a.isInsideClipVolume();
    bool v2In = m_b.isInsideClipVolume();
    std::pair<bool,Vector3> planIntersectPoint[6];
    uint8_t intesectPlanCount = 0;
    if (!v1In&&!v2In)
    {
        //pos x
        intesectPlanCount+= planIntersectPoint[0].first= (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(1, 0, 0), Vector3(1, 0, 0), planIntersectPoint[0].second));
        //neg x
        intesectPlanCount += planIntersectPoint[1].first = (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(-1, 0, 0), Vector3(-1, 0, 0), planIntersectPoint[1].second) );
        //pos y
        intesectPlanCount += planIntersectPoint[2].first = (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, 1, 0), Vector3(0, 1, 0), planIntersectPoint[2].second) );
        //neg y
        intesectPlanCount += planIntersectPoint[3].first = (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, -1, 0), Vector3(0, -1, 0), planIntersectPoint[3].second) );
        //pos z
        intesectPlanCount += planIntersectPoint[4].first = (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, 0, 1), Vector3(0, 0, 1), planIntersectPoint[4].second) );
        //neg z
        intesectPlanCount += planIntersectPoint[5].first = (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, 0, -1), Vector3(0, 0, -1), planIntersectPoint[5].second) );
        if (intesectPlanCount ==2)
        {
            Vector3 tempV1, tempV2;
            bool firstFilled = false;
            for (auto t:planIntersectPoint)
            {
                if (t.first) {
                    if (!firstFilled)
                    {
                        tempV1 = t.second;
                        firstFilled = true;
                    }
                    else
                    {
                        tempV2 = t.second;
                    }
                }
            }
            newLine = Line(tempV1, tempV2, this->m_color);
            return true;
        }

        return false;
    }
    if(v1In&&v2In)
    {
        newLine = *this;
        return true;
    }
  
    Vector3 temp;
    //pos x
    if (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(1, 0, 0), Vector3(1, 0, 0),temp))
    { 
        newLine = Line(v1In ? m_a : temp, v2In ? m_b : temp, this->m_color);
        return true;
    }
    //neg x
    if (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(-1, 0, 0), Vector3(-1, 0, 0),temp))
    {
        newLine = Line(v1In ? m_a : temp, v2In ? m_b : temp, this->m_color);
        return true;
    }
    //pos y
    if (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, 1, 0), Vector3(0, 1, 0),temp))
    {
        newLine = Line(v1In ? m_a : temp, v2In ? m_b : temp, this->m_color);
        return true;
    }
    //neg y
    if (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, -1, 0), Vector3(0, -1, 0),temp))
    {
        newLine = Line(v1In ? m_a : temp, v2In ? m_b : temp, this->m_color);
        return true;
    }
    //pos z
    if (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, 0, 1), Vector3(0, 0, 1),temp))
    {
        newLine = Line(v1In ? m_a : temp, v2In ? m_b : temp, this->m_color);
        return true;
    }
    //neg z
    if (Vector3::intersectPointInClipVolume(m_b - m_a, m_a, Vector3(0, 0, -1), Vector3(0, 0, -1),temp))
    {
        newLine = Line(v1In ? m_a : temp, v2In ? m_b : temp, this->m_color);
        return true;
    }
    //newLine = *this;
    return false;


}
void Line::draw(uint32_t* m_Buffer,int width,int hight)
{
    // Calculate differences
    int halfWidth = width / 2;
    int halfhight = hight / 2;
    int x1 = (m_a.x * halfWidth) + halfWidth;
    int x2 = (m_b.x * halfWidth) + halfWidth;
    int y1 = (m_a.y*halfhight)+halfhight;
    int y2 = (m_b.y * halfhight) + halfhight;


    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1; // Step for x
    int sy = (y1 < y2) ? 1 : -1; // Step for y
    int err = dx - dy;
    uint32_t color = m_color.getARGB();

    while (true)
    {
        //for debugging
        uint32_t* final = m_Buffer + ( ((y1 * width) + x1));
        
        if ((y1 * width) + x1 < width * hight && (y1 * width) + x1 >= 0)
            m_Buffer[(y1 * width) + x1] = color;
        
        // Break when we reach the end point
        if (x1 == x2 && y1 == y2)
            break;

        // Calculate error and adjust positions
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// Print the line
void Line::print() {
    std::cout << "Line[";
    std::cout << "(" << m_a << ")" <<
        " -> (" << m_b << ")" << "]";

}

bool Line::isInClip()
{
    return m_a.isInsideClipVolume()&&m_b.isInsideClipVolume();
}
