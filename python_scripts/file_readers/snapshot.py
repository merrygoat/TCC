#!/usr/bin/env python3
"""
Module defining interface for reading and writing snapshots in various file formats. A snapshot is an object which
holds data about a configuration of particles at a single point in time. A series of snapshots can be used to describe
a trajectory in time.

The module defines:
  - stream_safe_open: a context manager to facilitate parsing both open file streams and paths with the same interface
  - NoSnapshotError: exception raised when a snapshot could not be read from the file
  - snapshot: the class containing the general snapshot interface
"""

import sys
import numpy
import contextlib
import abc


@contextlib.contextmanager
def stream_safe_open(path_or_file, mode='r'):
    """Context manager for parsers which accept an open file stream or a file path to open.
    :param path_or_file: either an open file stream (in which case the context manager does nothing and returns it)
        or a path (in which case the context manager will open this, return a stream and then clean up)
    :param mode: mode to open file in, 'r' for read, 'w' for write
    """
    if isinstance(path_or_file, str):
        file_object = file_to_close = open(path_or_file, mode)
    else:
        file_object = path_or_file
        file_to_close = None

    try:
        yield file_object
    finally:
        if file_to_close:
            file_to_close.close()


class NoSnapshotError(RuntimeError):
    """Exception raised when not able to read a snapshot from a file."""
    pass


class SnapshotIncompleteError(RuntimeError):
    """Exception raised when a snapshot is partially read
    but not all particles are found or the coordinates cannot be read."""
    pass


class Snapshot:
    """Snapshot of a system of particles. A snapshot is a single configuration of particles at a point in time.
    Variables:
        num_particles: number of particles (integer)
        dimensionality: dimensionality of configuration space (integer)
        particle_coordinates: particle coordinates (num_particles by dimensionality container)
        box: box containing the particles (d by 2 container)
        species: labels of the particle species (string or container of strings)
        time: time or frame of the snapshot within a trajectory (integer or float)
    """

    def __init__(self, particle_coordinates=numpy.empty((0, 0)), box=None, species=None, time=0):
        """Create a new snapshot.
        :param particle_coordinates: list of paticle coordinates
        :param box: list of dimensions of box contatining the particles
        :param species: labels of the particle species
        :param time: time or frame number of the snapshot within a trajectory
        """
        self.particle_coordinates = particle_coordinates
        self.box = box
        if species is None:
            self.species = ['A'] * self.num_particles
        else:
            self.species = species
        self.time = time

    def copy(self):
        """
        :return: A deep copy of the snapshot.
        """
        return Snapshot(self.particle_coordinates.copy(), self.box.copy(), self.species.copy(), self.time)

    @property
    def num_particles(self):
        """
        :return: Number of particles in snapshot.
        """
        return len(self.particle_coordinates)

    @property
    def dimensionality(self):
        """
        :return: Dimensionality of configuration space.
        """
        return self.particle_coordinates.shape[1]

    @classmethod
    def read_trajectory(cls, path_or_file, num_frames=1):
        """A generator that snapshots from a file.

        To return all snapshots at once use the list function:
        >>> list(Snapshot.read_trajectory('trajectory.atom', 2))
        [<snapshot n=10976 t=0>, <snapshot n=10976 t=1>]

        To iterate over snapshots use a for loop
        >>> data_set = Snapshot.read_trajectory('trajectory.atom', 2)
        >>> for frame in data_set:
        >>>     # Do science with frame
        Raises NoSnapshotError if file could not be read.
        Raises RuntimeException file format is not recognised
        :param path_or_file: file stream or path to read trajectory from
        :param num_frames: Will read this many frames from the trajectory
        """
        with stream_safe_open(path_or_file) as f:
            frames_read = 0
            while frames_read < num_frames:
                snap = cls()
                snap.read(f)

                yield snap
                frames_read += 1

    def write(self, output_file=sys.stdout):
        """Dump the snapshot to a file.
        :param output_file: file or path to write the snapshot to
        """
        with stream_safe_open(output_file, 'w') as output_file:
            xyz_frame = str(self)
            output_file.write(xyz_frame)
            output_file.write('\n')

    def __repr__(self):
        """Internal representation of the object for printing to debugger."""
        return '<snapshot n=%r t=%r>' % (self.num_particles, self.time)

    @abc.abstractmethod
    def __str__(self):
        """
        String representation of the snapshot in the chosen format not implemented in the base class,
         and must be written for specific formats.
        """
        raise NotImplementedError

    @abc.abstractmethod
    def read(self, file_or_stream):
        """
        Function to read a snapshot from a file. Not implemented in base class and must be written
        for specific file formats.
        """
        raise NotImplementedError
