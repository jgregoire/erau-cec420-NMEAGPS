/* File: NMEAMessage.hpp
 * Author: Elliot Robinson
 * Date modified: 5 Oct, 2011
 * Changes:
 *   5 Oct, 2011: Inititial creation
 */

#ifndef NMEAMESSAGE_HPP
#define NMEAMESSAGE_HPP


virtual class NMEAMessage
{
  public:
    NMEAMessage() {;}
    virtual ~NMEAMessage();
  private:
    virtual void parse(NMEASentence sentence);
    virtual void updateData();
};

#endif
