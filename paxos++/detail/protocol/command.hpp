/*!
  Copyright (c) 2012, Leon Mergen, all rights reserved.
 */

#ifndef LIBPAXOS_CPP_DETAIL_PROTOCOL_COMMAND_HPP
#define LIBPAXOS_CPP_DETAIL_PROTOCOL_COMMAND_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/serialization/access.hpp>

#include "../remote_server.hpp"

namespace paxos { namespace detail { namespace protocol {

/*!
  \brief Describes command that is exchanged between servers
 */
class command
{
public:

   friend class boost::serialization::access;

   enum type
   {
      type_invalid,

      //! Sent by a host to initiate a handshake
      type_handshake_start,
      
      //! Sent as a response to a handshake request
      type_handshake_response,

      //! Sent when a node in the quorum claims leadership
      type_leader_claim,

      //! Sent when a node acknowledges a new leader
      type_leader_claim_ack,

      //! Sent when a node rejects a new leader
      type_leader_claim_reject,

      //! Sent when a leader connects to a node to announce they are the leader
      type_leader_announce,

      //! Sent by a client to the leader when it wants to initiate a new request
      type_request_initiate,

      //! Sent by a leader to all the followers when they must all prepare a request
      type_request_prepare,

      //! Sent by all followers as a response to the prepare command
      type_request_promise,

      //! Sent by followers to leader if an inconsistency in the proposal ids has been detected
      type_request_fail,

      //! Sent by leader to all followers after they have sent a promise
      type_request_accept,

      //! Sent by followers to leader after they have accepted and processed a request
      type_request_accepted,
   };

public:

   /*!
     \brief Default constructor
    */
   command ();

   static command
   from_string (
      std::string const &               string);

   static std::string
   to_string (
      command const &                   command);

   void
   set_type (
      enum type                         type);

   enum type
   type () const;

   void
   set_host_id (
      boost::uuids::uuid const &        id);

   boost::uuids::uuid const &
   host_id () const;

   void
   set_host_endpoint (
      boost::asio::ip::tcp::endpoint const &    endpoint);

   boost::asio::ip::tcp::endpoint
   host_endpoint () const;

   void
   set_host_state (
      enum remote_server::state state);

   enum remote_server::state
   host_state () const;

   void
   set_proposal_id (
      uint64_t                  proposal_id);

   uint64_t
   proposal_id () const;

   void
   set_workload (
      std::string const &       byte_array);

   std::string const &
   workload () const;

private:

   template <class Archive>
   void serialize (
      Archive &                 ar,
      unsigned int const        version);
   
private:

   enum type                    type_;

   boost::uuids::uuid           host_id_;
   std::string                  host_address_;
   uint16_t                     host_port_;
   enum remote_server::state    host_state_;

   uint64_t                     proposal_id_;
   std::string                  workload_;
};

}; }; };

#include "command.inl"

#endif //! LIBPAXOS_CPP_DETAIL_TCP_CONNECTION_COMMAND_HPP
