{-# LANGUAGE Safe #-}
{- |
Module      : OMI.Port
Description : Normative Haskell EDSL for OMI-Port transforms.
Copyright   : (c) OMI Project
License     : All rights reserved

Defines the 'PortTensor_G' concept as a pure function:

    PortTensor_G(source, target) -> OMI_PortRoute

This is the normative reference for the C EABI implementation.
The C code in src/omi_port.c must match these semantics.

No connect, transmit, mount, validate, receipt, or accept state.
All authority flags default to False.
-}

module OMI.Port (
    -- * Types
    PortScope(..)
  , PortRoute(..)
  , PortAuthority(..)
  , PortResult(..)
    -- * Core transform
  , portTensor
  , isFGauge
    -- * Helpers
  , scopeFromString
  , isAuthoritative
  , hasSideEffects
  , flipCaseBit
  , chiralityBit
  , isOmicronAscii
) where

import Data.Char (chr, ord)
import Data.Bits (xor, (.&.), shiftR)
import Data.Word (Word8, Word16, Word32)

-- | URI-CIDR scope: @<uri>#/<prefix>@
data PortScope = PortScope
    { scopeUri  :: String
    , scopePrefixLen :: Word8
    } deriving (Eq, Show)

-- | Authority flags — all default to False (dormant)
data PortAuthority = PortAuthority
    { authConnects   :: Bool
    , authTransmits  :: Bool
    , authMounts     :: Bool
    , authAccepted   :: Bool
    , authValidated  :: Bool
    , authReceipted  :: Bool
    } deriving (Eq, Show)

-- | Canonical FS/GS/RS/US route
data PortRoute = PortRoute
    { routeGauge  :: Word8
    , routeFs     :: Word16
    , routeGs     :: Word16
    , routeRs     :: Word16
    , routeUs     :: Word16
    , routeFsI    :: Word16
    , routeGsI    :: Word16
    , routeRsI    :: Word16
    , routeUsI    :: Word16
    , routeReg    :: Word32
    , routeStack  :: Word32
    , routeCar    :: Word32
    , routeCdr    :: Word32
    , routeAuthority :: PortAuthority
    } deriving (Eq, Show)

-- | Result type for port operations
data PortResult
    = Ok
    | ErrorNullInput
    | ErrorScopeMalformed
    | ErrorScopeNoPrefix
    | ErrorScopeBadPrefix
    | ErrorScopeTooLong
    | ErrorInvalidGauge
    | ErrorUnspecified
    deriving (Eq, Show)

-- | Default dormant authority (all flags False)
defaultAuthority :: PortAuthority
defaultAuthority = PortAuthority False False False False False False

-- | Mix a scope into an accumulator (matches C implementation)
mixScope :: PortScope -> Word32 -> Word32
mixScope (PortScope uri plen) acc0 =
    let byteAcc = Prelude.foldl (\a c -> a * 31 + fromIntegral (ord c)) acc0 uri
    in byteAcc * 31 + fromIntegral plen

-- | Check if gauge is in F0..FF range
isFGauge :: Word8 -> Bool
isFGauge g = g >= 0xF0 && g <= 0xFF

-- | Parse URI-CIDR string into PortScope
scopeFromString :: String -> Either PortResult PortScope
scopeFromString s =
    case break (== '#') s of
        (_, "")          -> Left ErrorScopeNoPrefix
        (uri, '#':'/':rest) ->
            if Prelude.null uri || length uri > 255
                then Left ErrorScopeTooLong
                else case reads rest of
                         [(n, "")] | (n :: Int) >= 0 && (n :: Int) <= 255 ->
                             Right (PortScope uri (fromIntegral n))
                         _ -> Left ErrorScopeBadPrefix
        _                -> Left ErrorScopeNoPrefix

-- | Extract bits [n, n+16) as Word16
pick16 :: Word32 -> Int -> Word16
pick16 w n = fromIntegral ((w `shiftR` n) .&. 0xFFFF)

-- | Core transform: PortTensor_G(source, target) -> route
portTensor :: PortScope -> PortScope -> Word8 -> Either PortResult PortRoute
portTensor source target gauge
    | not (isFGauge gauge) = Left ErrorInvalidGauge
    | otherwise =
        let acc0 = mixScope source 0
            acc1 = acc0 * 31 + fromIntegral gauge
            acc  = mixScope target acc1
        in Right PortRoute
            { routeGauge  = gauge
            , routeFs     = pick16 acc 0
            , routeGs     = pick16 acc 8
            , routeRs     = pick16 acc 16
            , routeUs     = pick16 acc 24
            , routeFsI    = pick16 acc 4
            , routeGsI    = pick16 acc 12
            , routeRsI    = pick16 acc 20
            , routeUsI    = pick16 acc 28
            , routeReg    = acc
            , routeStack  = acc `xor` 0xDEADBEEF
            , routeCar    = acc `xor` 0xCAFEBABE
            , routeCdr    = acc `xor` 0xBAADF00D
            , routeAuthority = defaultAuthority
            }

-- | Check if authority flags represent an authoritative state
isAuthoritative :: PortAuthority -> Bool
isAuthoritative a = authAccepted a && authValidated a && authReceipted a

-- | Check if authority flags indicate side effects
hasSideEffects :: PortAuthority -> Bool
hasSideEffects a = authConnects a || authTransmits a || authMounts a

-- | Omicron ASCII check
isOmicronAscii :: Char -> Bool
isOmicronAscii c = c == 'o' || c == 'O'

-- | Chirality bit: 1 for lowercase, 0 for uppercase
chiralityBit :: Char -> Int
chiralityBit c
    | isOmicronAscii c = if ord c .&. 0x20 /= 0 then 1 else 0
    | otherwise        = 0

-- | Flip case via XOR with 0x20
flipCaseBit :: Char -> Char
flipCaseBit c
    | isOmicronAscii c = chr (ord c `xor` 0x20)
    | otherwise        = c
